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

#define _CRT_SECURE_NO_WARNINGS
#include<forwin.h>
#define ALLEGWIN
#include <allegext.h>
#include<string.h>
#include "bib_e.h"
#include "rysuj_e.h"

#ifdef  ALLEGWIN
#define LINE myline
#define CIRCLE mycircle
#else
#define LINE line
#define CIRCLE circle
#endif


#define y_21 19
#define y_3 0

extern void setcolor(int kolor);
extern void setlinestyle1(int line_style, unsigned short u_pattern, int thickness);
extern void setwritemode( int mode );
extern void myline(int x1, int y1, int x2, int y2);
extern void putpixel_(int x, int y, int color);
extern void mycircle(int x, int y, int radius);
extern void outtextxy(int x, int y0, const char *textstring);
extern void gettextsettings(struct textsettingstype  *texttypeinfo);
extern void change_font(int nr_font);
extern int getx(void);
extern int gety(void);
extern int getcolor(void);
extern void outtext(const char *textstring);
extern void outtext_(BITMAP *ui_screen, const char *textstring);
extern int textwidth(const char  *textstring);
extern int my_text_length(FONT *font, const char *text);

extern BITMAP *Get_Screenplay(void);

void outtext_r(char *textstring);

typedef struct
{
  int x, y ;
  unsigned char ch ;
}
T_Pl_Znak ;

static double ddX, ddY;
static int v1, h1;
static int s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;
static double wsph;

/*173-127*/
static char  PL[256-127]=
  "       a      c AEel  C  S   L s ZZoOnNzz                                                                       "
  "                 " ;

static int kolor;

int text_width(char *textstring) ;
//static void outtext_rs(char *) ;

void outtext_rs(char *textstring);

int iround(double val)
{
	return (int)(val + 0.5);
}


static void noopb (int x, int y)
{
  x = x ;
  y = y ;
}


#define noop noopb

static void set_par(void)
{
  setcolor (kolor) ;  /*????*/
  setlinestyle1 (SOLID_LINE, 0, NORM_WIDTH) ;
  setwritemode (COPY_PUT) ;
}
static void haczyk_d(int x, int y)
{
  set_par();
  LINE (x,y,x,y+v1);
  LINE (x,y+v1,x+h1,y+v1);
  if (HEIGHT>15)
   {
    LINE (x+1,y,x+1,y+v1);
    LINE (x,y+v1+1,x+h1,y+v1+1);
   }
}

static void haczyk_gm(int x, int y)
{
  set_par();
  LINE (x+2,y,x-h1+2,y+v1);
  if (HEIGHT>15)  LINE (x+3,y,x-h1+3,y+v1);
}

static void haczyk_gd(int x, int y)
{
  set_par();
  LINE (x+h1,y-v1+2,x-h1,y+v1);
  if (HEIGHT>15)  LINE (x+h1-1,y-v1+2,x-h1-1,y+v1);

}

static void a_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y=9*ddY+0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_d(x,y-y_3);

  }
static void e_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y=9*ddY+0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_d(x,y-y_3);

  }
static void c_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 3 * ddY + 0.5;
  y=y0+(int)ddY;
  d_x=3*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gm(x,y);

  }

static void s_(int x0, int y0)
{ int x,y;
  double d_x, d_y;

  d_y = 3 * ddY + 0.5;
  y = y0 + (int)ddY;
  d_x=3*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gm(x,y);

  }
static void z_(int x0, int y0)
{ int x,y;
  double d_x, d_y;

  d_y = 3 * ddY + 0.5;
  y = y0 + (int)ddY;
  d_x=3*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gm(x,y);

  }
static void n_(int x0, int y0)
{ int x,y;
  double d_x, d_y;

  d_y = 3 * ddY + 0.5;
  y = y0 + (int)ddY;
  d_x=3*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gm(x,y);

}
static void o_(int x0, int y0)
{ int x,y;
  double d_x, d_y;

  d_y = 3 * ddY + 0.5;
  y = y0 + (int)ddY;
  d_x=3*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gm(x,y);

  }
static void l_(int x0, int y0)
{ int x,y;
  double d_x, d_y;

  d_y=3*ddY+0.5;
  y=y0+(int)d_y;
  d_x=5*ddX+0.5;
  x=x0+(int)d_x -1;
  set_par();
  LINE(x,y,x-3,y+1);
  if (HEIGHT>15) LINE(x,y+1,x-3,y+2);

  }
static void x_(int x0, int y0)
{ int x,y;
  double d_x, d_y;

  d_y = 4 * ddY + 0.5;
  y = y0 + (int)ddY;
  d_x=2*ddX+0.5;
  x=x0+(int)d_x;
  set_par();
  LINE (x,y+v1,x+v1,y+v1);
  if (HEIGHT>15) LINE (x,y+v1-1,x+v1,y+v1-1);

  }

static void A_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y=9*ddY+0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_d(x,y-y_3);

  }

static void E_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y=9*ddY+0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_d(x,y-y_3);

  }
static void C_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 0; // -1 * ddY + 0.5;
  y=y0+(int)d_y;
  d_x=5*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gd(x,y);

  }
static void S_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 0;// -1 * ddY + 0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gd(x,y);

  }
static void Z_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 0; // -1 * ddY + 0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  set_par();
  haczyk_gd(x, y);

  }
static void N_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 0; // -1 * ddY + 0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gd(x,y);

  }
static void O_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 0; // -1 * ddY + 0.5;
  y=y0+(int)d_y;
  d_x=4*ddX+0.5;
  x=x0+(int)d_x;
  haczyk_gd(x,y);

  }
static void L_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y=3*ddY+0.5;
  y=y0+(int)d_y;
  d_x=2*ddX+0.5;
  x=x0+(int)d_x;
  set_par();
  LINE(x+2*h1,y+v1,x-(1*h1),y+(3*v1));
  if (HEIGHT>15) LINE(x+2*h1,y+v1-1,x-(1*h1),y+(3*v1)-1);

  }
static void X_(int x0, int y0)
{ int x,y;
  double d_x, d_y;
  d_y = 0; // -1 * ddY + 0.5;
  y=y0+(int)d_y;
  d_x=3*ddX+0.5;
  x=x0+(int)d_x;
  set_par();
 

  LINE (x,y,x+h1,y);
  LINE (x+h1,y,x+h1,y+1);
  LINE (x+h1,y+1,x,y+1);
  LINE (x,y+1,x,y);


  }


static void chr_252(int x0, int y0)
/*--------------------------------*/
{
	int x, y;
	y = y0;
	x = x0;
	outtextxy(x, y, "\xfc");
}
static void chr_252_ (int x0, int y0)  //3
/*--------------------------------*/
{

  int x, y ;

  y = y0 + s4 ;
  x = x0 ;
  set_par();
  LINE(x,y-s1,x+s1,y);   //0-1
  LINE(x + s1, y, x+s2,y); //1-2
  LINE(x + s2, y, x+s3,y);  //2-3
  LINE(x + s3, y, x+s4,y-s1);  //3-4
  LINE(x + s4, y - s1, x+s4,y-s2);  //4-5
  LINE(x + s4, y - s2, x+s3,y-s3);  //5-6
  LINE(x + s3, y - s3, x+s2,y-s3);   //6-7
  LINE(x + s3, y - s3, x+s4,y-s4);   //
  LINE(x + s4, y - s4, x+s4,y-s5);
  LINE(x + s4, y - s5, x+s3,y-s6);
  LINE(x + s2, y - s5, x+s1,y-s5);
  LINE(x + s1, y - s5, x,y-s4);

  LINE(x+s1,y-s1, x+s3,y-s1);
  LINE(x + s3, y - s1, x+s3,y-s2);
  LINE(x + s3, y - s2, x+s3,y-s4);

}

static void chr_255 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();

  LINE (x,y,x+s2,y);
  LINE (x,y,x,y+s2);
  LINE (x,y+s6,x,y+s8);
  LINE (x,y+s8,x+s2,y+s8);
  LINE (x+s6,y,x+s8,y);
  LINE (x+s8,y,x+s8,y+2);
  LINE (x+s8,y+s6,x+s8,y+s8);
  LINE (x+s8,y+s8,x+s6,y+s8);
}


static void fi_s (int x0, int y0)
/*-----------------------------*/
{
  int x, y;


  y = y0 ;
  x = x0 ;

  set_par() ;
  CIRCLE (x + s4, y + s5, s2);
  LINE (x + s5, y, x + s3, y + s10) ;
}

static void chr_177 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;

  y = y0+s1 ;
  x = x0 ;
  set_par() ;
  LINE (x,y+s2,x+s4,y+s2);
  LINE (x+s4,y+s2,x+s4,y+s5);
  LINE (x,y+s5,x+s4,y+s5);
  LINE (x,y+s2,x,y+s5);
  LINE (x+s3,y,x+s1,y+s7);
}
static void chr_178 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s2,x+s4,y+s2);
  LINE (x+s4,y+s2,x+s4,y+s5);
  LINE (x,y+s5,x+s4,y+s5);
  LINE (x,y+s2,x,y+s5);
  LINE (x+s3,y,x+s1,y+s7);
}
static void chr_179 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x+s1,y+s1,x+s4,y+s1);
  LINE (x+s1,y+s7,x+s4,y+s7);
  LINE (x+s2,y+s1,x+s2,y+s7);
}
static void chr_180 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y,x+s4,y);
  LINE (x,y+s7,x+s4,y+s7);
  LINE (x,y,x,y+s7);
}
static void chr_181 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s2,x,y+s6);
  LINE (x,y+s6,x+s4,y+s6);
}
static void chr_182 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s6,x+s4,y+s6);
  LINE (x+s2,y+s1,x+s2,y+s6);
}
static void chr_183 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s1,x+s4,y+s1);
  LINE (x+s2,y+s1,x+s2,y+s7);
}
static void chr_184 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y,x+s2,y);
  LINE (x+s2,y,x+s2,y+s7);
  LINE (x+s2,y+s7,x+s4,y+s7);
}
static void chr_185 (int x0, int y0)
/*-----------------------------*/
{
  int x, y;
  y = y0;
  x = x0;

  set_par();
  CIRCLE(x + s2, y + s5, s2);
  LINE(x + s4, y, x, y + s10);
  LINE(x, y + s10, x + s4, y + s10);
}
static void chr_186 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y,x+s1,y);
  LINE (x+s1,y,x+s1,y+s7);
  LINE (x,y+s7,x+s1,y+s7);
  LINE (x+s3,y,x+s4,y);
  LINE (x+s3,y,x+s3,y+s7);
  LINE (x+s3,y+s7,x+s4,y+s7);
}
static void chr_187 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y,x+s1,y);
  LINE (x,y,x,y+s7);
  LINE (x,y+s7,x+s1,y+s7);
  LINE (x+s3,y,x+s4,y);
  LINE (x+s4,y,x+s4,y+s7);
  LINE (x+s3,y+s7,x+s4,y+s7);
}
static void chr_188 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s2,x+s1,y+s2);
  LINE (x+s1,y+s2,x+s1,y+s5);
  LINE (x+s3,y+s2,x+s4,y+s2);
  LINE (x+s3,y+s2,x+s3,y+s5);
}
static void chr_189 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s2,x+s1,y+s2);
  LINE (x,y+s2,x,y+s5);
  LINE (x+s3,y+s2,x+s4,y+s2);
  LINE (x+s4,y+s2,x+s4,y+s5);
}
static void chr_190 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s5,x+s1,y+s5);
  LINE (x+s1,y+s2,x+s1,y+s5);
  LINE (x+s3,y+s5,x+s4,y+s5);
  LINE (x+s3,y+s2,x+s3,y+s5);
}
static void chr_191 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s5,x+s1,y+s5);
  LINE (x,y+s2,x,y+s5);
  LINE (x+s3,y+s5,x+s4,y+s5);
  LINE (x+s4,y+s2,x+s4,y+s5);
}

static void chr_192 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y+s4,x+s1,y+s4);
  LINE (x+s1,y+s4,x+s1,y+s6);
  LINE (x+s3,y+s3,x+s4,y+s3);
  LINE (x+s3,y+s1,x+s3,y+s3);
}

static void chr_193 (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x,y-s2,x,y+s3);
  LINE (x,y+s3,x+s4,y+s3);
}

static void chr_194 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0+s1 ;
  x = x0 ;
  set_par();
  LINE (x+s1,y-s2,x+s1,y+s9);
}



static void promil_s (int x0, int y0)
/*-----------------------------*/
{
  int x, y ;

  y = y0+2 ;
  x = x0 ;

  set_par();


  LINE(x + (7 * h1), y+v1, x + (1 * h1), y + (11 * v1));

  LINE(x + (2 * h1), y+v1, x + (4 * h1), y+v1);
  LINE(x + (2 * h1), y+2*v1, x + (4 * h1), y+2*v1);

  LINE(x + (3 * h1), y + (10 * v1), x + (5 * v1), y + (10 * v1));
  LINE(x + (3 * h1), y + (11 * v1), x + (5 * v1), y + (11 * v1));

  LINE(x + (7 * h1), y + (10 * v1), x + (9 * h1), y + (10 * v1));
  LINE(x + (7 * h1), y + (11 * v1), x + (9 * h1), y + (11 * v1));

}

static void chr_171 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}

static void chr_172(int x0, int y0)
/*--------------------------------*/
{
	int x, y;
	y = y0;
	x = x0;
	outtextxy(x, y, u8"\xac");
}

static void chr_224 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}

static void chr_225 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}

static void chr_226 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}

static void chr_227 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_228 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_229 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_230 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_231 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_234 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_235 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_238 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_239 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_240 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_241 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_242 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_243 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_244 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_245 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_246 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_247 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_248 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_249 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_250 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}
static void chr_251 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}

static void chr_253 (int x0, int y0)
/*--------------------------------*/
{
  int x, y ;
  y = y0 ;
  x = x0 ;
  outtextxy (x, y, u8" ") ;
}


static void (* pl_s[256-127])(int, int)=
{
  noop,noop,noop,noop,noop,noop,noop,a_,      /*127*-134*/
  noop,noop,promil_s,noop,noop,noop,c_,noop,  /*135-142*/
  A_,E_,e_,l_,noop,noop,C_,noop,noop,S_,      /*143-152*/
  noop,noop,noop,L_,noop,s_,noop,Z_,X_,o_,O_, /*153-163*/
  n_,N_,z_,x_,noop,noop,noop,chr_171,chr_172,       /*164-172*/
  noop,noop,noop,noop,chr_177,chr_178,chr_179,chr_180,chr_181,chr_182,  /*173-182*/
  chr_183,chr_184,chr_185,chr_186,chr_187,chr_188,chr_189,chr_190,chr_191,chr_192,  /*183-192*/
  chr_193,chr_194,noop,noop,noop,noop,noop,noop,noop,noop,  /*193-202*/
  noop,noop,noop,noop,noop,noop,noop,noop,noop,noop,  /*203-212*/
  noop,noop,noop,noop,noop,noop,noop,noop,noop,noop,  /*213-222*/
  noop,chr_224,chr_225,chr_226,chr_227,chr_228,chr_229,chr_230,chr_231,fi_s,  /*223-232*/
  noop,chr_234,chr_235,noop,fi_s,chr_238,noop,chr_240,chr_241,chr_242,         /*233-242*/
  chr_243,chr_244,noop,chr_246,chr_247,chr_248,chr_249,chr_250,chr_251,chr_252, /*243-252*/
  chr_253,noop,chr_255,                                             /*253-255*/
} ;


/*-----------------------------------------------------------------*/
/*----------------------------------------------------------------*/

#ifdef MENU_B

static void temp1 (int x, int y)     /*ogonek do n,s,c,z ...*/
/*------------------------------*/
{
#define dx1 2
#define dy1 4

   LINE (x, y,      x,      y - dy1) ;
   LINE (x, y,      x + dx1, y - dy1) ;
   LINE (x, y - dy1, x + dx1, y - dy1) ;
}

static void temp2 (int x, int y)     /*ogonek do a,e,A,E*/
/*------------------------------*/
{
#define dx 4
#define dy 3

   LINE (x,   y,      x,    y+dy-1) ;
   LINE (x+1, y+2,   x+1, y+2) ;
   LINE (x+1, y+dy-1, x+dx-1, y+dy-1) ;
   LINE (x+1, y+dy,   x+dx-1, y+dy) ;
}

static void temp3 (int x, int y)     /*kropka do z, Z*/
/*------------------------------*/
{
   LINE (x, y-2, x+1, y-2) ;
   LINE (x, y-1, x+1, y-1) ;
   LINE (x, y,   x+1, y  ) ;
}


static void a_b (int x, int y)
{
  temp2 (x - 6, y + y_21) ;
}

static void c_b (int x, int y)
{
  temp1 (x - 5, y + 9) ;
}

static void A_b (int x, int y)
{
  temp2 (x - 6, y + y_21) ;
}

static void E_b (int x, int y)
{
  temp2 (x - 6, y + y_21) ;
}

static void e_b (int x, int y)
{
  temp2 (x - 6, y + y_21) ;
}

static void l_b (int x, int y)
{
   LINE (x-6, y+15, x-1, y+10) ;
   LINE (x-6, y+16, x-1, y+11) ;
}

static void C_b (int x, int y)
{
  temp1 (x - 6, y + 5) ;
}

static void S_b (int x, int y)
{
  temp1 (x -6, y + 5) ;
}

static void L_b (int x, int y)
{
   LINE (x-6, y+15, x-1, y+10) ;
   LINE (x-6, y+16, x-1, y+11) ;
}

static void s_b (int x, int y)
{
  temp1 (x - 5, y + 9) ;
}

static void Z_b (int x, int y)
{
  temp1 (x - 6, y + 5) ;
}

static void X_b (int x, int y)
{
  temp3 (x - 7, y + 3) ;
}

static void o_b (int x, int y)
{
  temp1 (x - 5, y + 9) ;
}

static void O_b (int x, int y)
{
  temp1 (x - 6, y + 5) ;
}

static void n_b (int x, int y)
{
  temp1 (x - 6, y + 9) ;
}

static void N_b (int x, int y)
{
  temp1 (x - 8, y + 5) ;
}

static void z_b (int x, int y)
{
  temp1 (x - 6, y + 9) ;
}

static void x_b (int x, int y)
{
  temp3 (x - 6, y + 8) ;
}


static void (* pl_b[256-127])(int, int) =
{
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,a_b,
  noopb,noopb,noopb,noopb,noopb,noopb,c_b,noopb,
  A_b,E_b,e_b,l_b,noopb,noopb,C_b,noopb,noopb,S_b,
  noopb,noopb,noopb,L_b,noopb,s_b,noopb,Z_b,X_b,o_b,O_b,
  n_b,N_b,z_b,x_b,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,fi_s,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,noopb,
  noopb,noopb,noopb,
} ;


static void  get_text_justify (char *textstring, int *width, int *height)
/*--------------------------------------------------------------------------*/
{
  char unsigned *zn ;
  char t [MaxTextLen] ="" ;
  int k ;
  struct textsettingstype textinfo ;

  *width = 0 ;
  *height = 0 ;

  gettextsettings (&textinfo) ;
  if (textinfo.horiz == CENTER_TEXT)
  {
     k = 0 ;
     for (zn = (unsigned char*)textstring ; zn [0] != 0 ;  zn++)
     {
       if (' ' <= zn [0] && zn [0] <= '~')
       {
	      t [k++] = zn [0] ;
       }
       else
       if (zn [0] <= 255)
       {
	     t [k++] = PL [zn [0] - 127] ;
       }
       else
       {
	     t [k++] = ' ' ;
       }
     }
     t [k] = 0 ;
     *width = textwidth (t) ;
  }
}

int text_width1 (char *textstring)
/*-------------------------------*/
{
  char temp [2] ;
  int ret, len, i;

  len = strlen (textstring) ;
  temp [1] = '\0' ;
  ret = 0 ;
  for (i = 0; i < len; i++)
  {
    temp [0] = textstring [i] ;
    ret += textwidth (temp) ;
  }
  return ret ;
}

static void out_plzn (T_Pl_Znak *pl_zn, int plno)
/*----------------------------------------------*/
{
  int i ;

  for (i = 0 ; i < plno ; i++)
  {
    ( * pl_b [pl_zn [i].ch - 127] ) (pl_zn [i].x, pl_zn [i].y) ;
  }
}


void outtext_rb(char *textstring)
/*---------------------------------------*/
{
  char unsigned *zn ;
  char t [MaxTextLen] ="" ;
  T_Pl_Znak 	pl_zn [MaxTextLen] ;
  int k, plno = 0 ;
  int x, y, dxx, dyy  ;
  struct textsettingstype textinfo ;

  k = 0 ;
  x = getx () ;
  y = gety () ;
  kolor = getcolor () ;
  get_text_justify (textstring, &dxx, &dyy) ;
  for (zn = (unsigned char*)textstring ; zn [0] != 0 ;  zn++)
  {
    if (zn [0] <= '~')
    {
      t [k++] = zn [0] ;
    }
    else
    if (zn [0] <= 173)
    {
      t [k++] = PL [zn [0] - 127] ;
      t [k] = 0 ;
      pl_zn [plno].x = text_width1(t) + x - (dxx * WIDTH / 8 / 2) ;
      pl_zn [plno].y = y - dyy / 2 ;
      pl_zn [plno++].ch = zn [0] ;
    }
  }
  t [k] = 0 ;
  outtext (t) ;
  out_plzn (pl_zn, plno) ;
}


void outtext_r(char *textstring)
/*---------------------------------------*/
{
  struct textsettingstype textinfo;

  gettextsettings(&textinfo);
  if (textinfo.charsize == 1)
  {
    outtext_rs (textstring) ;
  }
  else
  {
    outtext_rb (textstring) ;
  }
}

#else

void outtext_r(char *textstring)
/*---------------------------------------*/
{
    outtext_rs (textstring) ;
}


#endif
/*----------------------------------------------------------------*/

static void  get_text_justify_rs (char *textstring, int *width, int *height)
/*--------------------------------------------------------------------------*/
{
  struct textsettingstype textinfo ;

  *width = 0 ;
  *height = 0 ;

  if (textstring == NULL)
	  return;


  if (textstring < (char *)255)
	  return;

  gettextsettings (&textinfo) ;

  if (textinfo.horiz == CENTER_TEXT)
  {
     *width = 8 * (int)strlen (textstring) - 2 ;
  }
  if (textinfo.vert == CENTER_TEXT)
  {
     *height = 8 ;
  }

}


static void out_plzn_rs (T_Pl_Znak *pl_zn, int plno)
//--------------------------------------------------
{
  int i ;
  char st1[2];

  for (i = 0 ; i < plno ; i++)
  {
    if (pl_zn [i].ch >= 127)
     {
      ( * pl_s [pl_zn [i].ch - 127] ) (pl_zn [i].x, pl_zn [i].y) ;
     }
     else
      {
        st1 [0] = pl_zn [i].ch;
        st1 [1] = '\0';
        outtextxy (pl_zn [i].x, pl_zn [i].y, st1) ;
      }
  }
}


void outtext_rs_ (BITMAP *ui_screen, char *textstring)
/*--------------------------------------------------*/
{
  unsigned char *zn ;
  char t [MaxMultitextLen +1] ="" ;
  T_Pl_Znak 	pl_zn [MaxMultitextLen +1] ;
  int k, plno = 0 ;
  int x, y, dxx, dyy  ;
  double pl_zn_x;
  double h1r, v1r;
  double dxx_r;

  if (textstring == NULL)
	  return;

  if (strlen(textstring) > MaxMultitextLen)  //must be something wrong
  {
	  *textstring = '\0';
	  return;
  }

  x = getx();
  y = gety() - 3;
  moveto(x, y);
  outtext_(ui_screen, textstring);
  return;



#ifdef ALLEGWIN
  change_font(0);
#else
  settextstyle(font_handle, HORIZ_DIR, 1);
#endif
  k = 0 ;
  x = getx () ;
  y = gety () -2;
  moveto(x, y); 
  kolor = getcolor () ;
  get_text_justify_rs (textstring, &dxx, &dyy) ;
  for (zn = (unsigned char*)textstring ; zn [0] != 0 ;  zn++)
  {
    if ((zn [0] <= '~') && (zn [0] >= ' '))
    {
      t [k++] = zn [0] ;
    }
    else
    if (zn [0] <= 255)
    {
      if (zn [0] < 30)
       {
         t [k++] = ' ' ;
       }
        else t [k++] = PL [zn [0] - 127] ;
      t [k] = 0 ;
      dxx_r=dxx;
      dxx_r *= WIDTH;
      dxx_r /= 16.0;
      pl_zn_x= (WIDTH) * (k - 1) + x - dxx_r + 2.5;
      pl_zn [plno].x = (int) pl_zn_x;
	  pl_zn[plno].y = y - dyy / 2;
      pl_zn [plno++].ch = zn [0] ;
    }
  }
  t [k] = 0 ;
  outtext (t) ; //64bit
  ddX = WIDTH;
  ddX /= 8;
  ddY = HEIGHT;
  ddY /= 12;
#ifdef ALLEGWIN
  change_font(1);
#else
  settextstyle(font_handle1, HORIZ_DIR, 1);
#endif

  wsph = (double)(HEIGHT) / 12.0;

  s1 = iround(1.0*wsph);
  s2 = iround(2.0*wsph);
  s3 = iround(3.0*wsph);
  s4 = iround(4.0*wsph);
  s5 = iround(5.0*wsph);
  s6 = iround(6.0*wsph);
  s7 = iround(7.0*wsph);
  s8 = iround(8.0*wsph);
  s9 = iround(9.0*wsph);
  s10 = iround(10.0*wsph);
  s11 = iround(11.0*wsph);
  s12 = iround(12.0*wsph);

  h1r =WIDTH / 8 + 0.5;
  v1r =HEIGHT/ 12 + 0.5; 
  h1 = (int) h1r;
  v1 = (int) v1r;
  x = getx ();
  y = gety ();

  out_plzn_rs (pl_zn, plno) ;
 
  moveto(x, y);
#ifdef ALLEGWIN
  change_font(0);
#else
  settextstyle(font_handle, HORIZ_DIR, 1);
#endif
}

void outtext_rs (char *textstring)
{
    //outtext_rs_ (screen, textstring);
    outtext_rs_ (Get_Screenplay(), textstring);
}

void outtext_r_(BITMAP *ui_screen, char *textstring)
/*------------------------------------------------*/
{
    outtext_rs_ (ui_screen, textstring) ;
}


int text_width(char *textstring)
/*-------------------------------*/
{
  char unsigned *zn;
  char t[MaxTextLen] ;

  t [0] = '\0' ;
  strcpy (t, textstring);
  for (zn = (unsigned char*)t; *zn!=0; zn++)
  {
    if (*zn > '~')
    {
      *zn = PL [*zn - 127];
    }
  }
  return textwidth(t);
}

