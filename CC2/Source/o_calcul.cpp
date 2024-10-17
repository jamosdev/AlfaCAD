/*   ______   ___       ___         ____     ______  ____
*   /\  _  \ /\_ \    /'___\       /\  _`\  /\  _  \/\  _`\
*   \ \ \L\ \\//\ \  /\ \__/   __  \ \ \/\_\\ \ \L\ \ \ \/\ \
*    \ \  __ \ \ \ \ \ \ ,__\/'__`\ \ \ \/_/_\ \  __ \ \ \ \ \
*     \ \ \/\ \ \_\ \_\ \ \_/\ \L\.\_\ \ \L\ \\ \ \/\ \ \ \_\ \
*      \ \_\ \_\/\____\\ \_\\ \__/.\_\\ \____/ \ \_\ \_\ \____/
*       \/_/\/_/\/____/ \/_/ \/__/\/_/ \/___/   \/_/\/_/\/___/
*
*   A CAD
*
*   By Marek Ratajczak 2024
*
*   See readme_alfacad.txt for copyright information.
*
*/

#include "forwin.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#ifndef LINUX
#include <dos.h>
#endif
#include <math.h>
#include "bib_e.h"
#include "rysuj_e.h"
#include "o_libfun.h"
#include "forlinux.h"

#include "leak_detector_cpp.hpp"

extern char* strlwr_(char* s);

extern "C" {
extern BOOL Check_if_Equal (double , double ) ;
extern BOOL Check_if_Equal2(double, double);
}

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/
#define MaxNameSize 50
const int variable = -1 ;
const int maxargs = 9 ;
typedef enum
{
  NAME, NUMBER, END, COMMA=',',
  PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
  PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
} t_token_value ;

typedef  double (*d_f_va)(double []) ;

struct name
{
  char 		*string ;
  struct 	name *next ;
  int		nargs ;
  int		insert ;
  union
  {
    double 	value ;
    d_f_va	funcptr ;
  } ;
} ;

const int TBLSZ = 23 ;
static name *table [TBLSZ] ;

static t_token_value 	curr_tok ;
static double 		number_value ;
static char 		name_string [MaxNameSize] ;
static int		b_err ;
static BOOL		b_insert_expr ;

static int poz_buf, len_buf ;
static char  *ptr_buf ;

static BOOL 		ini_buf 	(char *buf) ;
static void 		put_back 	(void) ;
static char 		get_char 	(void) ;
static BOOL 		get_buf_state 	(void) ;
static double    	get_number_value(void) ;
static void	      	skip_whitespace (void) ;

static double 		expr 		(void) ;
static double 		term 		(void) ;
static double 		prim 		(void) ;
static t_token_value 	get_token 	(void) ;
static name 		*look 		(char *, int);
static void 		free_store 	(void);
static double 		error 		(int no_err) ;
static BOOL		insertfunction  (char *funcname, int nargs, d_f_va funcptr) ;

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#define DEG_RAD (Pi2 / 360.)
#define RAD_to_DEG (360. / Pi2)
static double do_sqrt (double e [])
/*--------------------------------*/
{
  return (e [0] < 0)  ?  error (62) : sqrt (e[0]) ;
}

static double do_sin (double e [])
/*------------------------------*/
{
  return  sin (e[0] * DEG_RAD) ;
}

static double do_cos (double e [])
/*------------------------------*/
{
  return  cos (e[0] * DEG_RAD) ;
}

static double do_tan (double e [])
/*--------------------------------*/
{
  e [0] = Angle_Normal (e [0] * DEG_RAD) ;
  if (TRUE == Check_if_Equal (e [0], Pi2 / 4) ||
     TRUE == Check_if_Equal (e [0], Pi2 * 3 / 4) )
  {
    return error (65) ;
  }
  return tan (e[0]) ;
}

static double do_log (double e [])
/*--------------------------------*/
{
  return (e [0] <= 0)  ?  error (65) : log (e[0]) ;
}

static double do_log10 (double e [])
/*--------------------------------*/
{
  return (e [0] <= 0)  ?  error (65) : log10 (e[0]) ;
}

static double do_pow (double e [])
/*--------------------------------*/
{
  if (e [0] == 0 && e [1] <= 0)
  {
    return error (65) ;
  }
  if (e [0] < 0 && (int) e [1] != e [1])
  {
    return error (65) ;
  }
  return pow (e [0], e[1]) ;
}

static double do_min (double e [])
/*--------------------------------*/
{
  return min(e[0],e[1]) ;
}

static double do_min3 (double e [])
/*--------------------------------*/
{ double min1;
  min1=min(e[0],e[1]);
  return min(min1,e[2]) ;
}

static double do_max (double e [])
/*--------------------------------*/
{
  return max(e[0],e[1]) ;
}

static double do_max3 (double e [])
/*--------------------------------*/
{ double max1;
  max1=max(e[0],e[1]);
  return max(max1,e[2]) ;
}

static double do_asin (double e [])
/*--------------------------------*/
{
  return (e [0] > -1 && e [0] < 1) ? asin (e [0]) * RAD_to_DEG: error (65);
}

static double do_acos (double e [])
/*--------------------------------*/
{
  return (e [0] > -1 && e [0] < 1) ? acos (e [0]) * RAD_to_DEG : error (65);
}

static double do_atan (double e [])
/*--------------------------------*/
{
  return atan (e [0]) * RAD_to_DEG ;
}


static BOOL insert_function (void)
/*------------------------------*/
{
  BOOL b_ret ;

  b_ret = TRUE ;
  if (
  insertfunction ("sqrt", 1, do_sqrt) == FALSE ||
  insertfunction ("sin", 1, do_sin) == FALSE ||
  insertfunction ("cos", 1, do_cos) == FALSE ||
  insertfunction ("tan", 1, do_tan) == FALSE ||
  insertfunction ("log", 1, do_log) == FALSE ||
  insertfunction ("log10", 1, do_log10) == FALSE ||
  insertfunction ("pow", 2, do_pow) == FALSE ||
  insertfunction ("asin", 1, do_asin) == FALSE ||
  insertfunction ("acos", 1, do_acos) == FALSE ||
  insertfunction ("atan", 1, do_atan) == FALSE ||
  insertfunction ("min", 2, do_min) == FALSE ||
  insertfunction ("min2", 2, do_min)== FALSE ||
  insertfunction ("min3", 3, do_min3)==FALSE ||
  insertfunction ("max", 2, do_max)== FALSE ||
  insertfunction ("max2", 2, do_max)== FALSE ||
  insertfunction ("max3", 3, do_max3)==FALSE)
  {
    b_ret = FALSE ;
  }
  return b_ret ;
}

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

static BOOL ini_buf (char *buf)
/*-----------------------------*/
{
  if (buf == NULL)
  {
    return FALSE ;
  }
  ptr_buf = buf ;
  poz_buf = 0 ;
  len_buf = (int)strlen (ptr_buf) ;
  return TRUE ;
}

static void put_back (void)
/*-------------------------*/
{
  if (poz_buf > 0)
  {
    poz_buf-- ;
  }
}

static BOOL get_buf_state (void)
/*----------------------------*/
{
  BOOL retval ;

  retval = FALSE ;
  if (poz_buf < len_buf)
  {
    retval = TRUE ;
  }
  return retval ;
}

static char get_char (void)
/*------------------------*/
{
  char ch;

  ch = '\0' ;
  if (poz_buf < len_buf)
  {
     ch = ptr_buf [poz_buf++] ;
  }
  return ch ;
}

static double get_number_value (void)
/*---------------------------------*/
{
  double 	ret_val = 0 ;
  char 	*endptr ;

  ret_val = strtod ((char *)&ptr_buf [poz_buf], (char **)&endptr) ;
  poz_buf += (int)(endptr - ptr_buf - poz_buf) ;
  return ret_val ;
}

static void skip_whitespace (void)
/*-------------------------------*/
{
}

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

static double 		expr 		(void) ;
static double 		term 		(void) ;
static double 		prim 		(void) ;
static t_token_value 	get_token 	(void) ;
static name 		*look 		(char *, int);
static void 		free_store 	(void);
static double 		error 		(int no_err) ;

static double error (int no_err)
/*------------------------------*/
{
  b_err++;
  no_err = no_err;
  ErrList (no_err) ;
  return 1;
}


static name * look (char *p, int ins = 0)
/*-------------------------------------*/
{
  int ii = 0 ;						//hash
  char *pp = p ;
  while (*pp)
  {
    ii <<= 1 ;
    ii ^= *pp++ ;
  }
  if (ii < 0) ii = -ii;
  ii %= TBLSZ ;

  for (name * n = table [ii]; n; n=n->next)           //search
    if (strcmp (p,n->string) == 0) return n;

  if (ins == 0)  error (63) ;

  name *nn = new name ; 					//insert
  if (nn == NULL)
  {
    error (18) ;
    return NULL ;
  }
  nn->string = new char [strlen (p) + 1];
  if (nn->string == NULL)
  {
    error (18) ;
    return NULL ;
  }
  strcpy (nn->string, p) ;
  nn->nargs = variable ;
  nn->insert = 0;
  nn->value = 1; 		//niezbedne ze wzgledu na dzielenie przez 0
  nn->next = table [ii] ;
  table [ii] = nn ;
  return nn ;
}

static inline name *insert (char *s)
/*----------------------------------*/
{
  return look (s, 1) ;
}

static BOOL insertfunction (char *funcname, int nargs, d_f_va funcptr)
/*-------------------------------------------------------------------*/
{
  BOOL b_ret ;
  b_ret = FALSE ;
  name *n = insert (funcname) ;
  if (n != NULL)
  {
    b_ret = TRUE ;
    n->nargs = nargs ;
    n->funcptr = funcptr ;
  }
  return b_ret ;
}


static void free_store (void)
/*-------------------------*/
{
  int i;
  for (i = 0 ; i < TBLSZ ; i++)
  {
    name * n, * m;
    n = table [i] ;
    while (n)
    {
      delete n->string;
      m = n->next ;
      delete n;
      n = m;
    }
    table [i] = NULL;
  }
}


static double expr (void)
/*-----------------------*/
{
  double left ;

  left = term () ;
  for (;;)
  {
    switch (curr_tok)
    {
      case PLUS :
	get_token () ;
	left += term () ;
	break ;
      case MINUS :
	get_token () ;
	left -= term () ;
	break ;
      default :
	return left ;
    }
  }
}

static double term (void)
/*-----------------------*/
{
  double left, d ;

  left = prim () ;
  for (;;)
  {
    switch (curr_tok)
    {
      case MUL :
	get_token () ;
	left *= prim () ;
	break ;
      case DIV :
	get_token () ;
	d = prim () ;
	if (Check_if_Equal (d, 0) == TRUE)
	{
	  error (58) ;
	  return 1 ;
	}
	left /= d ;
	break ;
      default :
	return left ;
    }
  }
}

static double prim (void)
/*-------------------------*/
{
  double e ;

  switch (curr_tok)
  {
    case NUMBER :
      get_token () ;
      return number_value ;

    case NAME :
      if (get_token () == ASSIGN)
      {
	name * n = insert (name_string) ;
	get_token () ;
	n->value = expr () ;
	n->insert = 1 ;
	b_insert_expr = TRUE ;
	return n->value ;
      }
      else
      {
	if (curr_tok == LP)	//function calls
	{
	  name *n = look (name_string) ;
	  if (n == NULL)
	  {
	    return error (18) ;
	  }
	  if (n->nargs == variable)
	  {
	    return error (60) ;
	  }
	  get_token () ;	//skip LP

	  double e [maxargs] ;
	  int i = 0 ;
	  if (curr_tok != RP)
	  {
	    e [i++] = expr () ;
	  }

	  while (curr_tok == COMMA)
	  {
	    get_token () ;	//skip COMMA
	    e [i++] = expr () ;
	    if (i == maxargs)
	    {
	      break ;
	    }
	  }
	  if (curr_tok != RP)
	  {
	    return error (59) ;
	  }
	  get_token () ;    	//skip RP
	  if (n->nargs != i)
	  {
	    return error (61) ;
	  }
	  return (*n->funcptr)(e) ;
	}
	else
	{
	  name * n = look (name_string) ;
	  if (n == NULL)
	  {
	    return error (18) ;
	  }
	  if (n->nargs == variable)
	  {
	    if (n->insert == 0)
	    { error (57);
	    }
	    return n->value ;
	  }
	  else
	  {
	    return error (64) ;
	  }
	}
      }
      case MINUS :
      get_token () ;
      return - prim () ;
    case LP :
      get_token () ;
      e = expr () ;
      if (curr_tok != RP)
      {
	error (59) ;
	return 1 ;
      }
      get_token () ;
      return e ;
    case END :
      return 1 ;
    default :
      {	error (57) ;
	return 1 ;
      }
  }
}


static t_token_value get_token (void)
/*---------------------------------*/
{
  unsigned char ch ;

  do
  {
    if ( '\0' == (ch = get_char ()))
    {
      return curr_tok = END ;
    }
  }
  while (ch != '\n' && isspace(ch));

  switch (ch)
  {
    case ';' :
	case '|':
    case '\n' :
   skip_whitespace () ;
      return curr_tok = PRINT ;

    case '*' :
    case '/' :
    case '+' :
    case '-' :
    case '(' :
    case ')' :
    case '=' :
    case ',' :
      return curr_tok = (t_token_value)ch;

    case '0' : case '1' : case '2' :  case '3' :  case '4' :
    case '5' : case '6' : case '7':  case '8' :  case '9' :
    case '.' :
    put_back () ;
    number_value = get_number_value () ;
    return curr_tok = NUMBER ;

    default :	       // NAME, NAME= , or error
      if (isalpha (ch))
      {
	char *p = name_string ;
	*p++ = ch ;
	while ( '\0' != (ch = get_char ())  && isalnum (ch))
	{
	   *p++ = ch ;
	}
	put_back () ;
	*p = 0;
	return curr_tok = NAME ;
      }
      error (57) ;
      return curr_tok = PRINT ;
  }
}

static BOOL b__float = TRUE ;

extern "C" {

void Set_Float_Flag (BOOL b_float)
//--------------------------------
{
  b__float = b_float ;
}

int calculator (char *buf, int *retval_no, double *buf_ret)
{
  int no;
  double ret_expr;
  name * n ;
  int i,iii;
  char *pow_, *min_, *min2_, *min3_, *min4_, *min5_, *max_, *max2_, *max3_, *max4_, *max5_;

  //tutaj mozna sprawdzic czy wszystkie znaki zawieraja cyfry, kropke i przecinek
  //jezeli tak, i jezeli wystapil przecinek, mozna go zamienic na kropke
  pow_=strstr(buf,"pow(");
  min_=strstr(buf,"min(");
  min2_=strstr(buf,"min2(");
  min3_=strstr(buf,"min3(");
  min4_=strstr(buf,"min4(");
  min5_=strstr(buf,"min5(");
  max_=strstr(buf,"max(");
  max2_=strstr(buf,"max2(");
  max3_=strstr(buf,"max3(");
  max4_=strstr(buf,"max4(");
  max5_=strstr(buf,"max5(");

  if ((pow_==NULL) && (min_==NULL) && (min2_==NULL) && (min3_==NULL) && (min4_==NULL) && (min5_==NULL) && 
	  (max_==NULL) && (max2_==NULL) && (max3_==NULL) && (max4_==NULL) && (max5_==NULL)) 
  {
	  if (strchr(buf, ',')!=NULL)
	  {
		  iii=(int)strlen(buf);
		  for (i=0; i<iii; i++)  if (buf[i]==',') buf[i]='.';
	  }
  }

  b_err = 0;
  strlwr_ (buf) ;
  if (buf[strlen(buf)]!=';') strncat(buf,";",1);
  
  if (*retval_no <= 0   ||   buf_ret == NULL        ||
      buf_ret == NULL   || ini_buf (buf) == FALSE)
  {
    return 0;
  }
  n = insert ("pi") ;
  n->value =  3.1415926535897932385;
  n->insert = 1 ;
  n = insert ("e") ;
  n->value = 2.7182818284590452354;
  n->insert = 1 ;
  if (FALSE == insert_function ())
  {
    return 0 ;
  }
  no = 0;
  curr_tok = PRINT;
  while (get_buf_state () == TRUE)
  {
     get_token ();
    if (curr_tok == END) break ;
    if (curr_tok == PRINT) continue ;
    b_insert_expr = FALSE ;
    ret_expr = expr () ;
    if (curr_tok != END && curr_tok != PRINT && curr_tok != NAME)
    {
      error (57);
    }
    if (b_err > 0)
    {
      break;
    }
    if (b_insert_expr == FALSE)
    {
       buf_ret [no] = ret_expr ;
       if (b__float == TRUE)
       {
         buf_ret [no] = Double_to_Float (buf_ret [no]) ;
       }
       no++ ;
    }
    if (no >= *retval_no)
    {
      break;
    }
  }
  free_store ();
  *retval_no = no ;
  if (b_err > 0)
  {
    *retval_no = 0 ;
  }
  return ((b_err > 0 || no == 0) ? 0 : 1) ;
}

}


