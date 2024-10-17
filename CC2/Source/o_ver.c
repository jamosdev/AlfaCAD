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
#ifndef LINUX
#include <dos.h>
#include <io.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef LINUX
#include <unistd.h>
#else
#include<fcntl.h>
#endif

#include <time.h>
#include "bib_e.h"
#include "rysuj_e.h"
#include "b_messag.h"
#include "o_loadf.h"
#include "o_lfile.h"
#include "o_spec.h"

extern int ReadBlock_ (char *,double *,double *,RYSPOZ *,RYSPOZ *, char *, int , int *, BOOL) ;
extern int WriteBlock (char *,double ,double , char *, char *, int, int) ;
extern int Get_Legal_Key (char *legal);
extern int fnsplit (const char *path, char *drive, char *dir, char *name, char *ext);

#define   RYS_VER   "ALFVER.$1"
#define EXT_DIR   "*.*"

static char sz__file_mask [MAXFILE + MAXEXT] ;
static char sz__ext_dir [] = "*.*" ;
static char b__file ;
static FILE *stru__report ;
static BOOL b__ret ;


static BOOL change_file_ver (char *pathname)
/*----------------------------------------*/
{
  BOOL b_ret ;
  char sz_info [MaxTextLen] ;
  int i_rf ;

  b_ret = FALSE ;
  b__ret = TRUE ;
  zwolnienie_pamieci () ;
  if (b__file == TRUE)
  {
    i_rf = czytaj_zbior (pathname, TRUE, FALSE, TRUE) ;
    if (i_rf == IO_RET_FILE_TYPE_ERR)
    {
      return TRUE ;
    }
    if (i_rf == IO_RET_OK && IO_RET_OK == pisz_zbior (pathname, FALSE, 1))
    {
      b_ret = TRUE ;
    }
  }
  else
  {
    double  Px, Py ;
    char buf_name [Max_Spec_Value], buf_type [Max_Spec_Value] ;
    int lenmax = Max_Spec_Value ;
    int object_no ;

    i_rf = ReadBlock_ (pathname, &Px, &Py, &ADP, &ADK,
			 buf_name, lenmax, &object_no, FALSE) ;
    if (i_rf == IO_RET_FILE_TYPE_ERR)
    {
      return TRUE ;
    }

    if (i_rf == IO_RET_OK &&
	TRUE == Read_Spec_Block (pathname, buf_name, lenmax,
                buf_type, lenmax, TRUE) &&
	IO_RET_OK ==  WriteBlock (pathname, Px, Py, buf_name, buf_type, 0, 1))
    {
      b_ret = TRUE ;
    }
  }
  sprintf (sz_info, " %s - %s", ((b_ret == TRUE) ? "OK" : "ERROR"), pathname) ;
  InfoListStr (0, strrchr (sz_info, '/'/*'\\'*/) + 1) ;
  strcat (sz_info, "\n") ;
  if (stru__report != NULL)
    fputs (sz_info, stru__report) ;
  return b_ret ;
}

#ifdef test
static void test (void)
/*--------------------*/
{
   FILE *in ;
   char buf [100] ;

   if ((in = fopen ("alfrep1.ver", "rt")) == NULL)
   {
     return ;
   }
   while (!feof(in))
   {
     fgets (buf, 100, in) ;
     buf [strlen (buf) -1] = '\0' ;
     change_file_ver (buf) ;
   }
   fclose (in) ;
}
#endif

/*    win32todo

int time_cmp (struct tm *tblock, struct ftime *ptrs_ftime)
{
   int i_ret ;

   i_ret = -1 ;
   if (1900 + tblock->tm_year != 1980 + ptrs_ftime->ft_year)
   {
     if (1900 + tblock->tm_year > 1980 + ptrs_ftime->ft_year)
     {
       i_ret = 1 ;
     }
   }
   else
   if (1 + tblock->tm_mon  != ptrs_ftime->ft_month)
   {
     if (1 + tblock->tm_mon  > ptrs_ftime->ft_month)
     {
       i_ret = 1 ;
     }
   }
   else
   if (tblock->tm_mday != ptrs_ftime->ft_day)
   {
     if (tblock->tm_mday > ptrs_ftime->ft_day)
     {
       i_ret = 1 ;
     }
   }
   else
   if (tblock->tm_hour != ptrs_ftime->ft_hour)
   {
     if (tblock->tm_hour > ptrs_ftime->ft_hour)
     {
       i_ret = 1 ;
     }
   }
   else
   if (tblock->tm_min != ptrs_ftime->ft_min)
   {
     if (tblock->tm_min > ptrs_ftime->ft_min)
     {
       i_ret = 1 ;
     }
   }
   else
   if (tblock->tm_sec  != ptrs_ftime->ft_tsec * 2)
   {
     if (tblock->tm_sec  > ptrs_ftime->ft_tsec * 2)
     {
       i_ret = 1 ;
     }
   }
   else
   {
     i_ret = 0 ;
   }
   return i_ret ;
}

*/


/*   win32todo

static void change_dir_files_ver (char *pathname) 	//pathname zakonczone jest 
//----------------------------------------------
{
  struct ffblk ffblk;
  int done;

  struct ftime s_ftime ;
  time_t t;
  struct tm *tblock;

  t = time (NULL) ;
  tblock = localtime (&t) ;

  strcat (pathname, sz__file_mask) ;
  done = findfirst (pathname, &ffblk, FA_ARCH);
  pathname [strlen (pathname) - strlen (sz__file_mask)] = '\0' ;
  while (!done)
  {
    memcpy (&s_ftime, &ffblk.ff_ftime, 4) ;
    if ((ffblk.ff_attrib == FA_ARCH // || ffblk.ff_attrib == FA_NORMAL)
	 ) &&  
    
	time_cmp (tblock, (struct ftime *)&s_ftime) > 0)
    {
       strcat (pathname, strupr (ffblk.ff_name)) ;
       change_file_ver (pathname) ;
       pathname [strlen (pathname) - strlen (ffblk.ff_name)] = '\0' ;
    }

    done = findnext(&ffblk);
  }
}

*/

static void change_subdirs_ver (char *pathname) 	/*pathname zakonczone jest \*/
/*---------------------------------------*/
{
  int done;

/*  win32todo

  change_dir_files_ver (pathname) ;   
  strcat (pathname, sz__ext_dir) ;
  done = findfirst (pathname, &ffblk, FA_DIREC);
  pathname [strlen (pathname) - strlen (sz__ext_dir)] = '\0' ;
  while (!done)
  {
    if ( ffblk.ff_attrib == FA_DIREC && ffblk.ff_name [0] != '.' )
    {
       strcat (pathname, strupr (ffblk.ff_name)) ;
       strcat (pathname, "/") ;       //lub "\\"       
       change_subdirs_ver (pathname) ;
       pathname [strlen (pathname) - strlen (ffblk.ff_name) - 1] = '\0' ;
    }
    done = findnext(&ffblk);
  }

*/
}


BOOL Change_Version (char *pathname, BOOL b_file)
/*-----------------------------------------------*/
{
  char sz_pathname [MAXPATH] ;
  int key, k ;
  char  drive [MAXDRIVE], dir [MAXDIR], name [MAXFILE], ext [MAXEXT] ;
  int ret;

  fnsplit (pathname, drive, dir, name, ext) ;
  b__ret = FALSE ;
  b__file = b_file ;
  strcpy (sz_pathname, pathname) ;
  strcpy (sz__file_mask, name) ;
  strcat (sz__file_mask, ext) ;
  ret=unlink (RYS_VER) ;
  k = pisz_zbior (RYS_VER, FALSE, 1) ;
  if ( k )
  {
    ret=unlink (RYS_VER) ;
    return b__ret ;
  }
  if (strchr (sz__file_mask, '?') == NULL && strchr (sz__file_mask, '*') == NULL)
  {
    change_file_ver (sz_pathname) ;
  }
  else
  {
    strrchr (sz_pathname, '/'/*'\\'*/) [1] = '\0' ;   /*niebezpieczne !!!!*/
    komunikat (50) ;
    key = Get_Legal_Key ("TNtn\033") ;
    komunikat (0) ;
    if (key == 'N' || key == 'n')
    {
//      change_dir_files_ver (sz_pathname) ;   //win32todo
    }
    else
    if (key == 'T' || key == 't')
    {
      change_subdirs_ver (sz_pathname) ;
    }
  }
  if (b__ret == TRUE)
  {
    zwolnienie_pamieci () ;
    if (0 != czytaj_zbior (RYS_VER, FALSE, TRUE, TRUE))
    {
      ErrList (8) ;
    }
  }
  ret=unlink (RYS_VER) ;
  return b__ret ;
}



void Convert_Old_Block (void)
/*--------------------------*/
{
  char sz_file [MAXPATH] ;

  stru__report = NULL ;
  sz_file [0] = '\0' ;
  while (Load_File (sz_file, CONVERT_OLD_BLOCK, TRUE) == TRUE)
  {
    if (stru__report == NULL)
    {
      stru__report = fopen ( "ALFREP.VER", "wt" ) ;
    }
    Change_Version (sz_file, FALSE) ;
  }
  if (stru__report != NULL)
    fclose (stru__report) ;
}

void Convert_Old_File (void)
/*--------------------------------*/
{
  char sz_file [MAXPATH] ;

  stru__report = NULL ;
  sz_file [0] = '\0' ;
  while (Load_File (sz_file, CONVERT_OLD_FILE, TRUE) == TRUE)
  {
    if (stru__report == NULL)
    {
      stru__report = fopen ( "ALFREP.VER", "wt" ) ;
    }
    Change_Version (sz_file, TRUE) ;
  }
  if (stru__report != NULL)
    fclose (stru__report) ;
}



