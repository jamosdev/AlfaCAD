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
#define ALLEGWIN
#include <allegext.h>
#include <math.h>
#include <stddef.h>
#include "bib_e.h"
#include "b_clip.h"
#include "rysuj_e.h"

////#include "leak_detector_c.h"

#define MaxNumPolygonPoints 200

extern void Get_View_Coord (int * x1, int *y1, int *x2, int *y2) ;
extern void fillpoly(int numpoints, void *polypoints);
extern void fillpoly3D(int numpoints, void *polypoints, void *polypoints_z, int bg);
extern void drawpoly(int numpoints, void *polypoints);
extern void putpixel_(int x, int y, int color);
extern int getcolor(void);

extern int get_palette_color(int color);

extern void fillpolypattern(int numpoints, AL_CONST int* polypoints, char* s_pattern, long origin_x, long origin_y);
extern void my_fillpoly(int numpoints, int* polypoints, int translucency, int kolory_paper);

void Clip_Solid (int num_we, T_PixelTVal  *poly_we, int *num_wy, int *poly_wy) ;
BOOL Clip_Solid0 (int num_we, T_PixelTVal  *poly_we, int *num_wy, int *poly_wy) ;

static void clip (int granica,
			T_PixelTVal  x1, T_PixelTVal  y1,
			T_PixelTVal  x2, T_PixelTVal  y2,
			T_PixelTVal  *x, T_PixelTVal  *y) ;
static BOOL widocznosc (int granica, T_PixelTVal  x1, T_PixelTVal  y1) ;

static void clipF(int granica,
	T_Float  x1, T_Float  y1,
	T_Float  x2, T_Float  y2,
	T_Float *x, T_Float  *y);
static BOOL widocznoscF(int granica, T_Float  x1, T_Float  y1);


static int wg, wp, wd, wl ;
static float wgf, wpf, wdf, wlf;

void Draw_Solid (int numpoints, T_PixelTVal * polypoints, unsigned int pcx_solid, BOOL hatch_solid, double origin_x, double origin_y, char *s_pattern, int translucency)
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
{
  int num_wy ;
  int *poly_wy ;

  if (numpoints>4)
  {
      int a=0;
  }

  if (NULL == (poly_wy = (int*)malloc((MaxNumPolygonPoints + 2) * sizeof(poly_wy[0]))))
  {
	  return;
  }

  if (FALSE == Clip_Solid0 (numpoints, polypoints, &num_wy, poly_wy))
  {
    Clip_Solid (numpoints, polypoints, &num_wy, poly_wy) ;
 }

  if ((pcx_solid==0) || (options1.fill_pcx_solid==1)) 
  {
      if (s_pattern != NULL)
      {
          fillpolypattern(num_wy, poly_wy, s_pattern, (long)origin_x, (long)origin_y);
      }
      else
         my_fillpoly (num_wy, poly_wy, translucency, kolory.paper) ;
  }

  free(poly_wy);

}



BOOL Clip_Solid0 (int num_we, T_PixelTVal  *poly_we,
			int *num_wy, int *poly_wy)
/*--------------------------------------------------*/
{
  int i, num_we2 ;
  T_PixelTVal dist ;
  BOOL b_ret ;

  *num_wy = num_we;
  b_ret = FALSE ;
  for (i = 2, dist = 0, num_we2 = num_we * 2 ; i < num_we2 ; i+= 2)
  {
    dist += labs (poly_we [0] - poly_we [i]) +
	    labs (poly_we [1] - poly_we [i + 1]) ;
  }
  if ( dist/ num_we < 100)
  {
    for (i = 0 ; i < num_we2 ; i++)
      poly_wy [i] = (int)poly_we [i] ;
    *num_wy = num_we ;
    b_ret = TRUE ;
  }
  return b_ret ;
}


void Clip_Solid (int num_we, T_PixelTVal  *poly_we, int *num_wy, int *poly_wy)
/*--------------------------------------------------------------------------*/
{
  int i, licz, granica ;
  T_PixelTVal   s1, s2, p1, p2, x, y ;
  T_PixelTVal  *temp_wy, *chwil ;

  if (NULL == (chwil = (T_PixelTVal*)malloc(MaxNumPolygonPoints * sizeof(chwil[0]))))
  {
	  return;
  }

  if (NULL == (temp_wy = (T_PixelTVal*)malloc(MaxNumPolygonPoints * sizeof(temp_wy[0]))))
  {
    free(chwil);
    return;
  }

  num_we *= 2 ;
  Get_View_Coord (&wl, &wg, &wp, &wd) ;
  for (i = 0 ; i < num_we ; i++)  /*dla kazdej granicy*/
  {
    chwil [i] = poly_we [i] ;
  }
 
  for ( granica = 0; granica < 4; granica++)
  {
    licz = 0 ;
    s1 = chwil [num_we - 2] ;	/*punk S jest ostatnim punktem*/
    s2 = chwil [num_we - 1] ;
    for (i = 0 ; i < num_we ; i += 2) 	/*dla kazdego wierzcholka*/
    {
      p1 = chwil [i] ;			/*punkt P jest nastepny*/
      p2 = chwil [i + 1] ;
      if (TRUE == widocznosc (granica, p1, p2))  /*punkt p jest widoczny*/
      {
	    if (TRUE == widocznosc (granica, s1, s2)) /*punkt s jest widoczny*/
	    {
	      temp_wy [licz++] = p1 ;
	      temp_wy [licz++] = p2 ;
	    }
	    else	/*punkt s jest niewidoczny*/
	    {
	      clip (granica, s1, s2, p1, p2, &x, &y) ;
	      temp_wy [licz++] = x ;
	      temp_wy [licz++] = y ;
	      temp_wy [licz++] = p1 ;
	      temp_wy [licz++] = p2 ;
	    }
      }
      else	/*punkt p jest niewidoczny*/
      {
	    if (TRUE == widocznosc (granica, s1, s2))
	    {
	      clip (granica, s1, s2, p1, p2, &x, &y) ;
	      temp_wy [licz++] = x ;
	      temp_wy [licz++] = y ;
	    }
      }
      s1 = p1 ;
      s2 = p2 ;
    } 			/*nastepny punkt*/
    num_we = licz ;

    for (i = 0; i < num_we ; i++)
    {
      chwil [i] = temp_wy [i] ;
    }
  }
  for (i = 0; i < num_we; i++)
  {
    poly_wy [i] = (int)temp_wy [i] ;
  }
  *num_wy = num_we / 2 ;

  free(chwil);
  free(temp_wy) ;
}


static void clip (int granica,
			T_PixelTVal  x1, T_PixelTVal  y1,
			T_PixelTVal  x2, T_PixelTVal  y2,
			T_PixelTVal  *x, T_PixelTVal  *y)
/*------------------------------------------------------*/
{
  double r ;

  switch (granica)
  {
    case 0 :
      r = ((double)(wg - y1)) / (y2 - y1) ;
      *x = x1 + (T_PixelTVal )floor(.5 + (x2 - x1) * r) ;
      *y = wg ;
      break ;
    case 1 :
      r = ((double)(wp - x1)) / (x2 - x1) ;
      *y = y1 + (T_PixelTVal )floor(.5 + (y2 - y1) * r) ;
      *x = wp ;
      break ;
    case 2 :
      r = ((double)(wd - y1)) / (y2 - y1) ;
      *x = x1 + (T_PixelTVal )floor(.5 + (x2 - x1) * r) ;
      *y = wd ;
      break ;
    case 3 :
      r = ((double)(wl - x1)) / (x2 - x1) ;
      *y = y1 + (T_PixelTVal )floor(.5 + (y2 - y1) * r) ;
      *x = wl ;
      break ;
  }
}


static BOOL widocznosc (int granica, T_PixelTVal  x1, T_PixelTVal  y1)
/*---------------------------------------------------------------*/
{
  BOOL b_retval ;
  T_PixelTVal  v1 ;

  switch (granica)
  {
    case 0 :
       v1 =  -(wp - wl) * (wg - y1) ;
       break ;
    case 1 :
       v1 = (wd -wg) * (wp - x1) ;
       break ;
    case 2 :
       v1 = - (wl - wp) * (wd - y1) ;
       break ;
    case 3 :
       v1 = (wg - wd) * (wl -x1) ;
       break ;
  }
  b_retval = TRUE ;
  if (v1 <=0)
  {
     b_retval = FALSE ;
  }
  return b_retval ;
}



static void near sinX(int *X,int N)
{ double dk,kat=0;
  int i;
  dk=Pi/(2*(N-1));
  for(i=0,kat=0;i<N;i++,X++,kat+=dk) *X=sin(kat)*1000+0.5;
}


#define NPC 14
void Draw_Kolo (T_PixelTVal xr, T_PixelTVal yr, T_PixelTVal R)
{
  static int y[NPC] = {0,121,239,355,465,568,663,749,823,885,935,971,993,1000};
  static int z[NPC], *x, wsk=0;
  static T_PixelTVal R0;
  T_PixelTVal  xp, yp ;
  double  Xfact, Yfact;
  int i, N;
  long N0;
  int num_we ;
  T_PixelTVal *poly_we ;
  int num_wy ;
  int *poly_wy ;

  if (R <= 1)
  {
    putpixel_ ((int)xr, (int)yr, getcolor ()) ;
    return ;
  }
  if (NULL == (poly_we= (T_PixelTVal*)malloc(MaxNumPolygonPoints * sizeof(poly_we[0]))))
  {
    return ;
  }
  if (NULL == (poly_wy= (int*)malloc((MaxNumPolygonPoints + 2) * sizeof(poly_wy[0]))))
  {
    free(poly_we);
    return ;
  }

  Xfact = fabs(R * 0.001);
  Yfact = Xfact / sk_x;
  if (Xfact > 0.0)
   { if(Pi*R<NPC*7.5)
     { N0=3+R/20;
	x = z;
	if(wsk==0 || R0!=R)
	 { sinX(z,(int)N0);
	   wsk=1;
	   R0=R;
	 }
     }
     else { N0=NPC; x=y;}
     N = (int)N0 ;
     num_we = 0 ;
     for (i = 0; i < N ; i++)
     {
	xp = xr + x [N - i - 1] * Xfact ;
	yp = yr - x [i] * Yfact ;
	poly_we [num_we++] = xp ;
	poly_we [num_we++] = yp ;
     }
     for (i = 1; i < N ; i++)
     {
	xp = xr - x [i] * Xfact ;
	yp = yr - x [N - i - 1] * Yfact ;
	poly_we [num_we++] = xp ;
	poly_we [num_we++] = yp ;
     }
     for (i = 1; i < N ; i++)
     {
	xp = xr - x [N - i - 1] * Xfact ;
	yp = yr + x [i] * Yfact ;
	poly_we [num_we++] = xp ;
	poly_we [num_we++] = yp ;
     }
     for (i = 1; i < N - 1; i++)
     {
	xp = xr + x [i] * Xfact ;
	yp = yr + x [N - i - 1] * Yfact ;
	poly_we [num_we++] = xp ;
	poly_we [num_we++] = yp ;
     }
  }
  if (R < 50)
  {        	/*obcinanie pozostawiono funkcji fillpoly*/
    for (i = 0 ; i < num_we; i++)
      poly_wy [i] = (int)poly_we [i] ;
    num_wy = num_we / 2 ;
  }
  else
  {
    Clip_Solid (num_we / 2, poly_we, &num_wy, poly_wy) ;
  }
  fillpoly (num_wy, poly_wy) ;
  free(poly_we);
  free(poly_wy);
}

