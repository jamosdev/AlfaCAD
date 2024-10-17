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

#define __O_PLINE__
#include<forwin.h>
#define ALLEGWIN
#include <allegext.h>
#include<string.h>
#ifndef LINUX
#include<process.h>
#else
#endif
#include<ctype.h>
#ifndef LINUX
#include<io.h>
#include<dos.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>

#include "bib_e.h"
#include "rysuj_e.h"
#include "o_pline.h"
#include "o_libfun.h"

#include "menu.h"

extern int Pline_Line (double, double) ;
extern int Pline_Arc (double, double) ;
extern int last_pline_delete (void) ;
extern void Wymiarowanie_polilinii(char *adr0, int opcja);
extern void view_line_type(LINIA *L);
extern void Wymiarowanie_polilinii1(char *adr0, int opcja);
extern BOOL group_block_with_type (long dane_size000, double x, double y, char *blok_type0, char obiektt2, char *prefix, char kod_obiektu);

enum PLINE_MODE {PL_MODE_CONTINUE = 1 , PL_MODE_LINE , PL_MODE_ARC,
	PL_MODE_END, PL_MODE_UNDO } ;

int pline_trace=0;

/*-----------------------------------------------------------------------*/

static void erase_pline (void)
/*---------------------------*/
{
  BLOK *ptrs_block ;
  NAGLOWEK *nag ;

  nag = (NAGLOWEK*)dane ;
  ptrs_block = (BLOK*)dane ;
  if (nag->obiekt == OdBLOK &&
      ptrs_block->kod_obiektu == B_PLINE &&
     ptrs_block->dlugosc_opisu_obiektu == 1 &&
     ((ptrs_block->opis_obiektu [0] == PL_PLINE) ||
      (ptrs_block->opis_obiektu [0] == PL_PLYTA) ||
      (ptrs_block->opis_obiektu [0] == PL_OTWOR) ||
      (ptrs_block->opis_obiektu [0] == PL_SIEC)))

  {
    blokzap(dane, (char  *)(dane + nag->n), Anormalny, COPY_PUT, 0) ;
    usun_obiekt ((void *)dane) ;
  }
  else
  {
    ErrList (77) ;
  }
}

void erase_pline_ (void)
{
    erase_pline ();
}

static BOOL add_block (void)
/*------------------------*/
{
    BLOK s_blockd = Bdef ;  //TO CHECK
  BLOK *ptrs_block ;
  char c_pltype ;

  s_blockd.n = B3 + sizeof (c_pltype) ;
   s_blockd.kod_obiektu = B_PLINE ;
  s_blockd.dlugosc_opisu_obiektu = sizeof(c_pltype) ;
  if (OTWOR_P==TRUE) s_blockd.obiektt2=O2BlockAparat;
  if( (ptrs_block = (BLOK*)dodaj_obiekt (NULL, &s_blockd)) == NULL)
  {
    return FALSE ;
  }
  if (PLYTA==TRUE) c_pltype = PL_PLYTA;
    else if (OTWOR_P==TRUE) c_pltype = PL_OTWOR;
      else if (SIEC_P==TRUE) c_pltype = PL_SIEC;
        else c_pltype = PL_PLINE ;
  memmove ( &(ptrs_block->opis_obiektu [0]), &c_pltype, sizeof(c_pltype)) ;

  return TRUE ;
}

BOOL add_block_(void)
{
    return add_block();
}

static void redcr (char typ)
/*-------------------------*/
{
  static void (*CUR_oN)(double ,double);
  static void (*CUR_oFF)(double ,double);
  static int ( *SW[5])(),akt;
  if (typ == 0)
  {
     komunikat0 (80) ;
     akt = sel.akt ; sel.akt = ASel ;
     CUR_OFF (X, Y) ;
     CUR_oFF = CUR_OFF ;  CUR_OFF = cursel_off ;
     CUR_oN = CUR_ON ;   CUR_ON = cursel_on ;
     SW[0] = SERV [73] ;  SERV [73] = sel_t ;
     SW[1] = SERV [81] ;  SERV [81] = sel_d ;
     SW[4] = SERV [83];  SERV [83] = last_pline_delete ;
     CUR_ON (X, Y) ;
  }
  else
  {
     CUR_OFF (X, Y) ;
     CUR_OFF = CUR_oFF ;
     CUR_ON = CUR_oN ;
     SERV [73] = SW [0] ;
     SERV [81] = SW [1] ;
     SERV [83] = SW [4] ;
     CUR_ON (X, Y) ;
     sel.akt = akt ;
     komunikat0 (0) ;
   }
}


static BOOL get_start_pline (double *X0, double *Y0)
/*-----------------------------------------------*/
{
  EVENT *ev;

  redcr (0) ;
  while(1)
  {
    view_line_type(&LiniaG);
    ev = Get_Event_Point (NULL, X0, Y0) ;
    if (ev->What == evKeyDown)
    {
      if(ev->Number == 0)
      {
	    redcr (1) ;
	    return FALSE ;
      }
         if(ev->Number == ENTER)
      {
	    redcr (1) ;
	    return TRUE ;
      }
    }
    else if (ev->What == evCommandP)
    {
        printf("%d",ev->Number);
    }

  }
}

BOOL get_start_pline_ (double *X0, double *Y0)
{
    return get_start_pline (X0, Y0);
}

void set_pline_param (BOOL b_pline)
/*---------------------------------------*/
{
   if (b_pline == TRUE)
   {
     if (PLYTA==TRUE)
       {
         LiniaG.obiektt2 = O2BlockSpecial ;
         LukG.obiektt2 = O2BlockSpecial ;
       }
       else
       if (OTWOR_P==TRUE)
        {
          LiniaG.obiektt2 = O2BlockAparat ;
          LukG.obiektt2 = O2BlockAparat ;
        }
        else
        if (SIEC_P==TRUE)
         {
           LiniaG.obiektt2 = O2BlockAparat ;
           LukG.obiektt2 = O2BlockAparat ;
         }
        else
         {
           LiniaG.obiektt2 = O2BlockPline ;
           LukG.obiektt2 = O2BlockPline ;
         }
   }
   else
   {
     LiniaG.obiektt2 = O2NoBlockS ;
     LukG.obiektt2 = O2NoBlockS ;
   }
}


void Pline (void)
/*--------------*/
{
  double X0, Y0, df_xbeg, df_ybeg ;
  int pline_mode ;
  TEXT TextGa=Tdef;
  int LengthT;
  double angle_l, sina, cosa;
  double dy_komentarz = 3.5;
  double dx_komentarz = 0.5;
  char opis_plyty[31];

  pline_trace=0; //pline

  set_pline_param (TRUE) ;
beg:
  if (FALSE == add_block ())
  {
    set_pline_param (FALSE) ;
    return ;
  }
start:
  if (FALSE == get_start_pline (&X0, &Y0))
  {
    set_pline_param (FALSE) ;
    erase_pline () ;
    return ;
  }
  pline_mode = PL_MODE_LINE ;
  df_xbeg = X0 ;
  df_ybeg = Y0 ;

  if (PLYTA==TRUE)  //dopisanie tekstu
   {
    strcpy(opis_plyty,"");
    if (read_esc(opis_plyty,30,181)==0)
    {
      ;
    }
    angle_l=get_angle_l();
    sina=get_sina();
    cosa=get_cosa();
    /*OPIS*/
    TextGa.kat= (angle_l/360) * Pi2;
    TextGa.wysokosc=2;
    TextGa.italics=0;
    TextGa.width_factor=1;
    TextGa.warstwa=Current_Layer;
    TextGa.kolor=LiniaG.kolor;
    TextGa.czcionka=8;
    TextGa.typ=n_typ_komentarz;
    TextGa.justowanie=j_do_lewej;
    TextGa.ukryty=0;
    TextGa.obiektt1 = 0;
    TextGa.obiektt2 = O2NoBlockS;
    TextGa.blok=1;


    TextGa.x=X0 + (dx_komentarz * cosa) + (dy_komentarz * sina);
    TextGa.y=Y0 - (dy_komentarz * cosa) + (dx_komentarz * sina);

    strcpy(&TextGa.text[0],opis_plyty);
    LengthT=strlen(TextGa.text);
    TextGa.dl=LengthT;
    TextGa.n=T18+TextGa.dl;
  
    if (dodaj_obiekt((BLOK*)dane, (void*)&TextGa)!=NULL)
     {
       rysuj_obiekt((char*)&TextGa,COPY_PUT,1);
     }
   }

  while (1)
  {
    if (pline_mode == PL_MODE_LINE)
    {
      pline_mode = Pline_Line (df_xbeg, df_ybeg) ;
    }
    else
    {
      pline_mode = Pline_Arc (df_xbeg, df_ybeg) ;
    }
    if (PL_MODE_END == pline_mode)
    {
      goto beg ;
    }
    else
    if (PL_MODE_UNDO == pline_mode)
    {
      goto start ;
    }
  }
}


int Pline_single (double *x_begin, double *y_begin)
/*-----------------------------------------------*/
{
  double X0, Y0, df_xbeg, df_ybeg ;
  int pline_mode ;

  set_pline_param (TRUE) ;
beg1:
  if (FALSE == add_block ())
  {
    set_pline_param (FALSE) ;
    return 0;
  }
start1:
  if (FALSE == get_start_pline (&X0, &Y0))
  {
    set_pline_param (FALSE) ;
    erase_pline () ;
    return 0;
  }
  pline_mode = PL_MODE_LINE ;
  df_xbeg = X0 ;
  df_ybeg = Y0 ;
  while (1)
  {
    if (pline_mode == PL_MODE_LINE)
    {
      pline_mode = Pline_Line (df_xbeg, df_ybeg) ;
    }
    else
    {
      pline_mode = Pline_Arc (df_xbeg, df_ybeg) ;
    }
    if (PL_MODE_END == pline_mode)
    {
      *x_begin=X0;
      *y_begin=Y0;
      return 1;
    }
    else
    if (PL_MODE_UNDO == pline_mode)
    {
      goto start1 ;
    }
  }
}

int Pline_single_xy (double *x_begin, double *y_begin)
/*--------------------------------------------------*/
{
  double X0, Y0, df_xbeg, df_ybeg ;
  int pline_mode ;

  set_pline_param (TRUE) ;
beg2:
  if (FALSE == add_block ())
  {
    set_pline_param (FALSE) ;
    return 0;
  }
  view_line_type(&LiniaG);
  X0=X;
  Y0=Y;

  pline_mode = PL_MODE_LINE ;
  df_xbeg = X0 ;
  df_ybeg = Y0 ;
  while (1)
  {
    if (pline_mode == PL_MODE_LINE)
    {
      pline_mode = Pline_Line (df_xbeg, df_ybeg) ;
    }
    else
    {
      pline_mode = Pline_Arc (df_xbeg, df_ybeg) ;
    }
    if (PL_MODE_END == pline_mode)
    {
      *x_begin=X0;
      *y_begin=Y0;
      return 1;
    }
    else
    if (PL_MODE_UNDO == pline_mode)
    {
      return 0;
    }
  }
}


void PlineW1 (char *blok_type)
/*--------------------------*/
{
  double X0, Y0, df_xbeg, df_ybeg ;
  int pline_mode ;
  long dane_size000, dane_size0000;

  set_pline_param (TRUE) ;
beg:

  dane_size0000=dane_size;

  if (FALSE == add_block ())
  {
    set_pline_param (FALSE) ;
    return ;
  }
start:
  if (FALSE == get_start_pline (&X0, &Y0))
  {
    set_pline_param (FALSE) ;
    erase_pline () ;
    return ;
  }
  pline_mode = PL_MODE_LINE ;
  df_xbeg = X0 ;
  df_ybeg = Y0 ;
  while (1)
  {
    if (pline_mode == PL_MODE_LINE)
    {
      pline_mode = Pline_Line (df_xbeg, df_ybeg) ;
    }
    else
    {
      pline_mode = Pline_Arc (df_xbeg, df_ybeg) ;
    }
    if (PL_MODE_END == pline_mode)
    {
      Wymiarowanie_polilinii1(dane, 0);
      dane_size000=dane_size-dane_size0000;
      if (dane_size000>0)
      {
        group_block_with_type(dane_size000,0,0,blok_type, O2NoBlockS, "", B_WIRE);   //L'č'
      }

      goto beg ;
    }
    else
    if (PL_MODE_UNDO == pline_mode)
    {
      goto start ;
    }
  }
}

#undef __O_PLINE__
