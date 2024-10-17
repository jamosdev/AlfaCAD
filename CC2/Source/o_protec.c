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

#include <forwin.h>
#include <stdlib.h>
#ifndef LINUX
#include <dos.h>
#endif
#include <stdio.h>
#ifdef LINUX
#include <unistd.h>
#endif
#include <time.h>
#include <math.h>
#ifndef LINUX
#include <process.h>
#else

#endif
#include <string.h>
#ifndef LINUX
#include<io.h>
#endif
#include<fcntl.h>
#include "bib_e.h"

#define FALSE               0
#define TRUE                1


#include "o_protec.h"

#include "leak_detector_c.h"

/*--------------------------------------------------*/


#define BUF_LEN  60000u
#define DBUF_LEN 220

extern char* Get_Date (int off);
extern long	random(void);

static char sz_prot_key [PROT_KEY_LEN] = PROT_KEY ;
static int b_out_err = TRUE ;

int Get_New_Off_Xor (int off_xor)
/*------------------------------*/
{
  int ret ;

  ret = 13 + 5 * off_xor / 4 ;
  return ret ;
}


void Out_Prot_Err (int err)
/*--------------------------*/
{
  if (FALSE == b_out_err)
  {
    return ;
  }
  switch (err)
  {
    case 1:
      printf ("Brak pami�ci !!!\n") ;
      break ;
    case 2:
      printf ("Brak zbioru !!!\n") ;
      break ;
    case 3:
      printf ("B��dna operacja dyskowa !!!\n") ;
      break ;
    case 4:
      printf ("Brak nazwy zbioru !!!\n") ;
      break ;
    case 5:
      printf ("Zbyt du�y numer !!!\n") ;
      break ;
    case 6:
      printf ("reinstal alf.exe 1 (zapamietanie) lub 2 (odtworzenie)\n") ;
      break ;
    default :
      break ;
  }
}

static int my_comp (const char *s1, const char *s2, int n)
/*-------------------------------------------------------*/
{
  int i ;

  i = 0 ;
  for (i = 0 ; s1 [i] == s2 [i] ; i++ )
  {
    if (i == n - 1)
      return 1 ;
  }
  return 0 ;
}

static unsigned my_search (char *ptr_buf, unsigned k)
/*---------------------------------------------------*/
{
  unsigned i, l_ret = -1 ;

  for ( i = 0 ; i < k ; i++)
  {
    if (ptr_buf [i] == sz_prot_key [0] &&
	0 == memcmp (&ptr_buf [i], sz_prot_key, PROT_KEY_LEN))
    {
      l_ret = i ;
      break ;
    }
  }
  return l_ret ;
}

BOOL File_Prot_Proc (char *ptrsz_file, BOOL (*proc)(char*), BOOL b_save)
/*---------------------------------------------------------------*/
{
  int fsrc ;
  char *buf = NULL ;
  int err = 0 ;
  long l ;
  unsigned buf_pos, k ;
  BOOL b_proc_ret ;

  if (ptrsz_file == NULL)
  {
    err = 4 ;
    goto lab0 ;
  }
  buf = (char *) malloc (BUF_LEN) ;
  if (buf == NULL)
  {
    err = 1 ;
    goto lab0 ;
  }
  fsrc = open (ptrsz_file, O_RDWR|O_BINARY) ;
  if (fsrc == -1)
  {
    err = 2 ;
    goto lab0 ;
  }
  l = 0 ;
  do
  {
    k = read (fsrc, (char*)buf, BUF_LEN) ;
    if (k == (unsigned)-1)
    {
      err = 3 ;
      goto lab0 ;
    }
    if (k > 0)
    {
      if ((unsigned)(-1) != (buf_pos = my_search (buf, k - DBUF_LEN)))
      {
        b_proc_ret = proc (&buf [buf_pos]) ;
        if (b_proc_ret == TRUE && b_save == TRUE)
        {
	  if (l != lseek (fsrc, l, SEEK_SET))
	  {
	    err = 3 ;
	    goto lab0 ;
	  }
	  if (k != write (fsrc, (char*)buf, k))
	  {
	    err = 3 ;
	    goto lab0 ;
	  }
        }
	break ;
      }
      l += k - DBUF_LEN ;
      if (l != lseek (fsrc, l, SEEK_SET))
      {
	err = 3 ;
	goto lab0 ;
      }
    }
  }
  while (k == BUF_LEN) ;

  if (-1 == close (fsrc))
  {
    err = 3 ;
    goto lab0 ;
  }
lab0:
  if (err > 0)
  {
    Out_Prot_Err (err) ;
  }
  if (buf != NULL)
  {
    free (buf) ;
  }
  return (err == 0) ? TRUE : FALSE ;
}


int File_Prot (char *ptrsz_file, BOOL (*proc)(char*))
/*---------------------------------------------------*/
{
  return File_Prot_Proc (ptrsz_file, proc, TRUE) ;
}

/*--------------------------------------------------*/


static char sz_xor_data [10] ;
int  off_xor ;


static char get_date_off (int off)
{          
  char dmr ;

  return 0;   //win32todo
}

char* Get_Date (int off)
{
  off_xor = off ;
  sz_xor_data [0] = get_date_off (0) ;
  sz_xor_data [1] = get_date_off (1) ;
  sz_xor_data [2] = get_date_off (3) ;
  sz_xor_data [3] = get_date_off (4) ;
  sz_xor_data [4] = get_date_off (6) ;
  sz_xor_data [5] = get_date_off (7) ;
  return sz_xor_data ;
}


static BOOL remove_prot (char* ptrsz_buf)
/*---------------------------------------*/
{
  T_Prot_Date *ptrs_prot_date ;

   ptrs_prot_date = (T_Prot_Date *)ptrsz_buf ;
   ptrs_prot_date->rom_mdr_tab [0].b_use = 1 ;
   ptrs_prot_date->rom_mdr_tab [0].off = off_xor ;
   memcpy (ptrs_prot_date->rom_mdr_tab [0].rom_mdr, sz_xor_data, 6) ;
   ptrs_prot_date->b_prot = 1 ;
   return TRUE ;
}


void Put_Data_To_File (char * ptrsz_file)
/*--------------------------------------*/
{
   File_Prot  (ptrsz_file, remove_prot) ;
}


extern T_Prot_Date *Get_Prot_Date (void) ;

int Check_Prot (void)
/*-------------------*/
{
  T_Prot_Date * ptrs_prot ;
  ptrs_prot = Get_Prot_Date () ;
  if (ptrs_prot->b_work  == 0 && ptrs_prot->b_compare == 0)
  {
    return 0 ;
  }  
  return 1 ;
}

static BOOL compare_date (T_Prot_Date *ptrs_prot_date)
/*-------------------------------------------------*/
{
  int i ;
  BOOL b_ret = FALSE ;

  for (i = 0 ; i < USER_NO   ; i++)
  {
    if (FALSE == ptrs_prot_date->rom_mdr_tab [i].b_use)
    {
      continue ;
    }
    Get_Date (ptrs_prot_date->rom_mdr_tab [i].off) ;
    if (0 == memcmp ((char *)ptrs_prot_date->rom_mdr_tab [i].rom_mdr, (char *)sz_xor_data, 6))
    {
      b_ret = TRUE ;
      break ;
    }   
   // b_ret = TRUE ;
  }
  return b_ret ;
}



void Protection (char *ptrsz_file)
/*------------------------------*/
{
   T_Prot_Date *ptrs_prot_date ;

   ptrs_prot_date = Get_Prot_Date () ;   
   if (ptrs_prot_date->b_work == 1)
   {
     return ;
   }
   if (ptrs_prot_date->b_prot == 0)
   {
  /*   randomize () ;  */
     Get_Date (random ()) ;   

     b_out_err = FALSE ;
     Put_Data_To_File (ptrsz_file) ;
     b_out_err = TRUE ;
     ptrs_prot_date->b_compare = 1 ;
   }
   else
   {
     ptrs_prot_date->b_compare = 0 ;
     if (compare_date (ptrs_prot_date) == TRUE)
     {
	ptrs_prot_date->b_compare = 1 ;
     }
   }
}
/*--------------------------------------------------*/

