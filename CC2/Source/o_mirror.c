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

#define __O_MIRROR__
#include <forwin.h>
#define ALLEGWIN
#include <allegext.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "bib_e.h"
#include "rysuj_e.h"

#include "menu.h"

extern int Get_Current_Color (void) ;
extern BOOL Add_Block (char  *,char  *, long *, double, double, double, double, double, double, double, double, int) ;
extern void orto_l(LINIA *L, int *Orto_Dir);
extern void setfillstyle_(int pattern, int color);
extern void setcolor(int kolor);
extern char *find_block_atrybut(char *adrp, char *adrk, char atrybut);

static LINIA line_g = Ldef ;
static double df_apx1, df_apy1, df_apx2, df_apy2 ;
static BOOL b_delete_old = FALSE ;
static double kos,koc;
extern int Set_Orto_Dir (LINIA *L, int orto_dir);
extern double Atan2 (double y, double x);
extern BOOL Check_if_Equal (double x, double y);
extern void Out_Edited_Draw_Param (ESTR *lps_et, BOOL out);
extern void Rotate_Point (double, double, double, double, double, double, double *,double *) ;
#define r22 16


static double kos0,koc0;
static int strwyj;

BOOL get_b_delete_old(void)
{
	return b_delete_old;
}

TMENU mMirror = {2,0,0,26, 56,4,TADD | ICONS,CMNU,CMBR,CMTX,0,COMNDmnr,0,0,0,&pmMirror,NULL,NULL} ;


/*------  axis point 1 -------------------------*/
static void cur_offap1 (double x,double y)
{
  cursel_off (x, y) ;
}

static void cur_onap1 (double x,double y)
{
  cursel_on (x, y) ;
}

/*------  axis point 1 -------------------------*/

static void  cur_offap2 (double x, double y)
/*--------------------------------------*/
{
    flip_screen();
}

static void  cur_offap2__ (double x, double y)
/*--------------------------------------*/
{
  cursel_off (x, y) ;
  outlineor (&line_g, XOR_PUT, 0) ;
}

static void out_parametry_angle (double k)
/*----------------------------------------*/
{
    char buf [100];

    buf [0] = '\0' ;
    sprintf (buf, "%#12.9lg", k) ;
    strcpy(eL.st, buf);
    Out_Edited_Draw_Param ((ESTR *)&eL, TRUE) ;
}

static void  cur_onap2 (double x, double y)
/*--------------------------------------*/
{ double l,kat;

    LINIA L1;

  line_g.x2 = x ;
  line_g.y2 = y ;
  line_g.kolor = Get_Current_Color () ;
  outlineor (&line_g, COPY_PUT, 0) ;

    if (orto) {
        L1.x1 = line_g.x1;
        L1.y1 = line_g.y1;
        L1.x2 = line_g.x2;
        L1.y2 = line_g.y2;

        Orto_Dir = Set_Orto_Dir(&line_g, Orto_Dir);
        orto_l(&L1, &Orto_Dir);

        if (Check_if_Equal(line_g.x1, L1.x2)) kat=0.0;
        else kat=PI2;

    }
    else {
        l = sqrt((line_g.x2 - line_g.x1) * (line_g.x2 - line_g.x1) + (line_g.x2 - line_g.x1) * (line_g.x2 - line_g.x1));
        if (l) {
            koc = (line_g.x2 - line_g.x1) / l;
            kos = (line_g.y2 - line_g.y1) / l;
            kat = Atan2(line_g.y2 - line_g.y1, line_g.x2 - line_g.x1);
        }
        else {
            koc = 1;
            kos = 0;
            kat = 0;
        }
        if (kat < 0) kat = 2 * Pi + kat;
    }
    out_parametry_angle(kat*180/Pi);

  cursel_on(x, y);
}


static void make_mirror (void)
/*--------------------------*/
{
  long l_block_size ;
  LINIA L;
  CUR_OFF (X,Y) ;

    if (strwyj)
    {
        Rotate_Point(kos0, koc0, df_apx1, df_apy1, df_apx1+100, df_apy1, &df_apx2, &df_apy2);
    }
  else {
        if (orto) {
            L.x1 = df_apx1;
            L.y1 = df_apy1;
            L.x2 = df_apx2;
            L.y2 = df_apy2;
            orto_l(&L, &Orto_Dir);
            df_apx2 = L.x2;
            df_apy2 = L.y2;

        }
    }

  if (b_delete_old == TRUE)
  {
    blokzap (ADP, ADK, Ablok, COPY_PUT, 0) ;
    transformacja_blok (ADP, ADK, df_apx1, df_apy1, df_apx2, df_apy2, Tmirror,0) ;
    blokzap (ADP, ADK,Ablok,COPY_PUT,1);
  }
  else
  {
      blokzap (ADP, ADK,Ablok,COPY_PUT,1);
    Add_Block (ADP, ADK, &l_block_size, df_apx1, df_apy1, df_apx2, df_apy2, 0, 0, 0, 0, Tmirror) ;
  }
  CUR_ON (X,Y) ;
}

static void info_objects_status (BOOL b_draw)
/*------------------------------------------*/
{
	char *st;

  setfillstyle_(SOLID_FILL, BKCOLOR);
  bar (maxX / 2 + 1, 0, maxX / 2 + 8 * WIDTH + 2, HEIGHT + 1) ;
  if (b_draw == TRUE)
  {
    st = st_nodel ;
    if (b_delete_old == TRUE)
    {
      st = st_del ;
    }
    moveto(maxX/2+1,1);
    setcolor(kolory.ink);
    outtext_r (st) ;
    }
}


static int set_old_objects_status (int leave)
/*-----------------------------------------*/
{

  if (leave) b_delete_old = FALSE;
  else b_delete_old = TRUE;
  info_objects_status (TRUE) ;
  return 0 ;
}


BOOL axis_point (double *df_apx, double *df_apy)
/*-------------------------------------------------*/
{
  EVENT *ev;

  while(1)
  {
     ev = Get_Event_Point (NULL, df_apx, df_apy) ;
     if ((ev->What == evKeyDown) || (strwyj))
     {
       if (ev->Number == 0)
       {
	 return FALSE ;
       }
       else
       if ((ev->Number == ENTER) || (strwyj))
       {
	 return TRUE ;
       }
     }
     else
     if (ev->What == evCommandP)
     {
       if (ev->Number == 0)
       {
	     set_old_objects_status (1) ;
       }
	   else if (ev->Number == 1)
	   {
		   set_old_objects_status(0);
	   }
     }
   }
}


static int el_o (BOOL b_graph_value)
/*--------------------------------*/
{
    double a;

    b_graph_value = b_graph_value ;
    if (eL.val_no < 1) return 0;
    a = eL.values [0] ;
    kos0 = sin (a * Pi / 180) ;
    koc0 = cos (a * Pi / 180) ;
    strwyj = 1 ;
    return 1 ;
}


void redcrMP (int type, int type1)
/*---------------------------*/
{
  static int ( *SW[1]) () ;
  static void (*CUR_oN)(double ,double);
  static void (*CUR_oFF)(double ,double);
  static TMENU *menu;
  static char st[POLE_TXT_MAX];
  unsigned short cod = L' ';
  static int iconno=0;
  static int np;

  switch (type)
  {
    case 0 :
      komunikat0 (71) ;
      if (type1==0) info_objects_status (TRUE) ;
      CUR_OFF (X,Y) ;
      sel.akt = 1 ;
      sel.cur = 0 ;
      if (type1==0)
      {
      SW [0] = SERV [83] ;    SERV [83] = (int (*)(void)) set_old_objects_status;
      }
      CUR_oFF = CUR_OFF ; CUR_OFF = cur_offap1 ;
      CUR_oN = CUR_ON ;   CUR_ON = cur_onap1 ;
      getmenupini(&menu,st,&cod, &iconno);
      if (type1 == 0)
      {
	   menupini (&mMirror, _MIRROR_, _MIRROR_C_, 39) ;
      }
      else
       {
	menupini(menu,st,cod, iconno) ;
       }
      CUR_ON (X,Y) ;
      break ;
    case 1 :
      if (type1==0)
      {
       SERV [83] = SW [0] ;
       menupini(menu,st,cod, iconno) ;
       info_objects_status (FALSE) ;
      }
      return ;
    case 2 :
      komunikat0 (72) ;
	  CUR_OFF(X, Y);
      line_g.x1 = line_g.x2 = X ;
      line_g.y1 = line_g.y2 = Y ;
          eL.x=maxX-PL266;
          eL.y= ESTR_Y;
          eL.lmax=r22;
          eL.val_no_max = 1 ;
          eL.mode = GV_ANGLE ;
          eL.format = "%#10.5lg" ;
          eL.ESTRF=el_o;
          eL.extend = 0;
          np=dodajstr(&eL);
      CUR_oFF = CUR_OFF ; CUR_OFF = cur_offap2 ;
      CUR_oN = CUR_ON ;   CUR_ON = cur_onap2 ;
      CUR_ON (X,Y) ;
      break ;
    case 3 :
	  CUR_OFF(X, Y);
	  CUR_OFF = CUR_oFF;
	  CUR_ON = CUR_oN;
      SERV [83] = SW [0] ;
      usunstr(np);
      menupini(menu,st,cod, iconno) ;
      if (type1==0) info_objects_status (FALSE) ;
	  CUR_ON(X, Y);
      break ;
  }
}

int Mirror_Proc (void)
/*---------------------*/
{

aa:
  redcrMP (0,0) ;
  strwyj=0;
  if (FALSE == axis_point (&df_apx1, &df_apy1))
  {
    redcrMP (1,0) ;
    return 0;
  }
  redcrMP (2,0) ;
  strwyj=0;
  if (FALSE == axis_point (&df_apx2, &df_apy2))
  {
	redcrMP(3, 0);
    goto aa ;
  }
  redcrMP (3,0) ;
  make_mirror () ;
  return 1;
}

int Mirror_Proc_X (void)
/*---------------------*/
{ NAGLOWEK *nag;
  BLOK *ptrs_block;
  T_Desc_Ex_Block		*ptrs_desc_bl ;
  BOOL axis_ok;
  BOOL b_delete_old_;
  char *adp;

 b_delete_old_ = b_delete_old;
 axis_ok=FALSE;
 b_delete_old = TRUE ;
//odszukanie poczatku bloku pod adresem ADP
 adp=find_block_atrybut(dane,dane+dane_size,Ablok);
 if (adp!=NULL)
  {
   ptrs_block=(BLOK *)adp;
   if (ptrs_block->dlugosc_opisu_obiektu > 1)
     {
      ptrs_desc_bl	= (T_Desc_Ex_Block *)(&ptrs_block->opis_obiektu	[0]) ;
      df_apx1=ptrs_desc_bl->x-10;
      df_apx2=ptrs_desc_bl->x+10;
      df_apy1=ptrs_desc_bl->y;
      df_apy2=ptrs_desc_bl->y;
      axis_ok=TRUE;
     }
  }

if (axis_ok==FALSE)
 {
  b_delete_old = b_delete_old_;
  return 0;
 }

  Orto_Dir = I_Orto_XDir;
  make_mirror () ;

  b_delete_old = b_delete_old_;
  return 1;
}


int Mirror_Proc_Y (void)
/*---------------------*/
{ NAGLOWEK *nag;
  BLOK *ptrs_block;
  T_Desc_Ex_Block		*ptrs_desc_bl ;
  BOOL axis_ok;
  BOOL b_delete_old_;
  char *adp;

 b_delete_old_ = b_delete_old;
 axis_ok=FALSE;
 b_delete_old = TRUE;
//odszukanie poczatku bloku pod adresem ADP
 adp=find_block_atrybut(dane,dane+dane_size,Ablok);
 if (adp!=NULL)
  {
   ptrs_block=(BLOK *)adp;
   if (ptrs_block->dlugosc_opisu_obiektu > 1)
     {
      ptrs_desc_bl	= (T_Desc_Ex_Block *)(&ptrs_block->opis_obiektu	[0]) ;
      df_apx1=ptrs_desc_bl->x;
      df_apx2=ptrs_desc_bl->x;
      df_apy1=ptrs_desc_bl->y-10;
      df_apy2=ptrs_desc_bl->y+10;
      axis_ok=TRUE;
     }
  }

 if (axis_ok==FALSE)
  {
   b_delete_old = b_delete_old_;
   return 0;
  }

  Orto_Dir = I_Orto_YDir;
  make_mirror () ;
  b_delete_old = b_delete_old_;
  return 1;
}

#undef __O_MIRROR__