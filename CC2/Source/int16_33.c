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
#endif
#include <stdlib.h>
#include <stdio.h>
#define ALLEGWIN
#include <allegext.h>

#include "bib_e.h"
#include "b_mouse.h"
#include "rysuj_e.h"

extern void (*MSERV)(int x,int y);
extern volatile char keys;
extern void _MouseClear(void);
extern int  Test_przycisniec0(int *keys);
extern void Odczyt_licznikow0(int *mouse_x, int *mouse_y);
extern void GrMouseGetEvent1(int flags,GrMouseEvent *event);
extern void GrMouseGetKeys(GrMouseEvent* event, int PozX, int PozY);
extern int my_poll_mouse(void);

extern BOOL get_sw_callback_locked(void);

extern void hide_x_cursor(void);
extern void show_x_cursor(void);
extern int Get_Global_Dialog_Flag(void);
extern void beep(long sound);
void free_mouse(void);

static int mouse_button_no = 2 ;
static BOOL locked_mouse;
static int gmaxx2, gmaxy2;
static int n_int_mouse=0;

static long mousetimestamp=0;
static long currentmousetimestamp=0;
static long breakmousetimestamp=0;
static BOOL breaktime=FALSE;
static int gesturetime=1; //2;  //2 sec
static MVECTOR mvector={0,{0},{0}};
static int K_num=3;
static int distx_free_mouse = 40, disty_free_mouse = 10;

static BOOL hardware_cursor_enabled=FALSE;


int PozX;
int PozY;

int PozX0;
int PozY0;


#define CORRECT_POSITION_MOUSE



#define MOUSE_COUNTER  500000 //2500
#define MOUSE_COUNTER2 1000

typedef struct _RECT { 
  long left; 
  long top; 
  long right; 
  long bottom; 
} RECT_, *PRECT_; 

void Set_Dist_Free_mouse(int distx, int disty)
{
    distx_free_mouse = distx;
    disty_free_mouse = disty;
}

void MouseClear(void)
{  
	_MouseClear();
}


void lock_mouse(void)
{

	locked_mouse=TRUE;
	gmaxx2 = getmaxx() / 2;
    gmaxy2 = getmaxy() / 2;

#ifdef LINUX
    hide_x_cursor();
#endif

    if (hardware_cursor_enabled==TRUE) disable_hardware_cursor();
    hardware_cursor_enabled=FALSE;

	scare_mouse();

    ini_cursor=FALSE;
}



void free_mouse(void)
{
	locked_mouse=FALSE;

	enable_hardware_cursor();
    hardware_cursor_enabled=TRUE;

#ifdef LINUX
    show_x_cursor();
#endif

    ini_cursor = TRUE;

}

void _free_mouse(void)
{

	locked_mouse=FALSE;

	enable_hardware_cursor();
    hardware_cursor_enabled=TRUE;

#ifdef LINUX
    show_x_cursor();
#endif
    ////unscare_mouse();

    Show_Mouse(X, Y) ;
    ini_cursor = TRUE;
}


int  Test_przycisniec1(int *keys)
{
  return Test_przycisniec0(keys);
}

void  Odczyt_licznikow1(void)
{ int mouse_x, mouse_y;

 Odczyt_licznikow0(&mouse_x, &mouse_y);
 MSERV(mouse_x,mouse_y);
 return;
}

void  Set_Mouse_Buttons_No (int mb_no)
/*--------------------------------------*/
{
  mouse_button_no = mb_no ;
}

/*________________________________________________________________________*/

void  Test_przycisniec(int *keys)
{ static GrMouseEvent event;

  GrMouseGetKeys(&event, PozX, PozY);
  *keys=event.flags;
}

void  Odczyt_licznikow(void) {
    int WspX, WspY, WspX1, WspY1;
    int d_mouse_x;
    int d_mouse_y;
    int top = MAXINT, bottom = -MAXINT, left = MAXINT, right = -MAXINT, sum, i;
    int dlx, dly, per;
    int midx, midy;
    int mv_max;

    get_mouse_mickeys(&WspX, &WspY);

    WspX1 = WspX;
    WspY1 = -WspY;

    MSERV(WspX1, WspY1);

    d_mouse_x = abs(mouse_x - gmaxx2);
    d_mouse_y = abs(mouse_y - gmaxy2);

    ///// shaking
    if (!Get_Global_Dialog_Flag()) {

        currentmousetimestamp = time(NULL);
        if ((!breaktime) || (currentmousetimestamp > breakmousetimestamp)) {
            breaktime = FALSE;
            if ((WspX != 0) || (WspY != 0)) {
                //continuouing

                mvector.x[mvector.no] = WspX1;
                mvector.y[mvector.no] = WspY1;

                midx = 0;
                midy = 0;
                top = MAXINT, bottom = -MAXINT, left = MAXINT, right = -MAXINT;
                mv_max = 0;
                for (i = 0; i < MV_MAX; i++) {

                    if ((mvector.x[i] != 0) && (mvector.y[i] != 0)) {

                        if (mvector.x[i] < left) left = mvector.x[i];
                        if (mvector.y[i] < top) top = mvector.y[i];
                        if (mvector.x[i] > right) right = mvector.x[i];
                        if (mvector.y[i] > bottom) bottom = mvector.y[i];

                        mv_max++;
                    }
                }
                if (mv_max > (MV_MAX / 2)) {

                    //printf("(%d) %d   %d   %d | %d   %d   %d\n", mv_max, left, midx, right, top, midy, bottom);

                    if (((right - midx > distx_free_mouse) && (midx - left > distx_free_mouse)) &&
                        ((bottom - midy < disty_free_mouse) && (midy - top < disty_free_mouse))) {
                        //beep(0x00000000L);
                        breaktime = TRUE;
                        breakmousetimestamp = time(NULL) + 2;
                        mvector.no = 0;
                        memset(mvector.x, 0, sizeof(mvector.x));
                        memset(mvector.y, 0, sizeof(mvector.y));
                        simulate_keypress(14592);
                    }
                }
                mvector.no++;
                if (mvector.no == MV_MAX) {
                    mvector.no = 0;
                    //printf("*\n");
                }

                mousetimestamp = currentmousetimestamp;
            } else if (currentmousetimestamp > (mousetimestamp + gesturetime)) {
                //resetting
                mvector.no = 0;
                memset(mvector.x, 0, sizeof(mvector.x));
                memset(mvector.y, 0, sizeof(mvector.y));
                mousetimestamp = currentmousetimestamp;
            }
        }
    }

    /////
	  if ((mouse_out == FALSE) && (sleep_state == TRUE) && ((abs(WspX) > 20) || (abs(WspY) > 20)))
	  {
		  sleep_state = FALSE;
	  }

#ifndef LINUX
	  if ((locked_mouse) && ((d_mouse_x > gmaxx2 / 3) || (d_mouse_y > gmaxy2 / 3)))  //  /2
	  {
		  n_int_mouse = 0;
#ifndef CORRECT_POSITION_MOUSE
		  position_mouse(gmaxx2, gmaxy2);
		  get_mouse_mickeys(&WspX, &WspY);
#else
		  position_mouse(gmaxx2, gmaxy2);
#endif
	  }
#endif

}


void  Odczyt_licznikow_resize(long *dx, long *dy)
{ int WspX,WspY,WspX1,WspY1;
  long msxL, msyL;
  int d_mouse_x, d_mouse_y;

  int p_mouse = poll_mouse();
  get_mouse_mickeys(&WspX, &WspY);
  if (WspX>32767) msxL=(WspX-65535); else msxL=WspX;
  if (WspY>32767) msyL=-(WspY-65535); else msyL=-WspY;
  WspX1=msxL;
  WspY1=msyL;


  d_mouse_x=abs(mouse_x-gmaxx2);
  d_mouse_y=abs(mouse_y-gmaxy2);

  if ((locked_mouse) && ((d_mouse_x>gmaxx2/2) || (d_mouse_y>gmaxy2/2)))
  {
	  n_int_mouse=0;
#ifndef CORRECT_POSITION_MOUSE
	  //odczytanie licznikow
      get_mouse_mickeys(&WspX, &WspY);
	  position_mouse(gmaxx2, gmaxy2);
	  //odczytanie licznikow
      get_mouse_mickeys(&WspX, &WspY);
#else
	 position_mouse(gmaxx2, gmaxy2);
#endif
  }

  *dx=WspX1;
  *dy=WspY1;

}

void  Set_Mouse_Buttons_No1 (int mb_no)
/*--------------------------------------*/
{
  mouse_button_no = mb_no ;
}

void  deinstal_ms(void)
{
 remove_mouse();
}



