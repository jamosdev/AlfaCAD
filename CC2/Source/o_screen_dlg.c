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

#define __O_SCREEN_DLG__
#pragma warning(disable : 4996)
#include<forwin.h>
#define ALLEGWIN
#include <allegext.h>
#include<string.h>
#ifndef LINUX
#include<dos.h>
#include<io.h>
#else
#include <unistd.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#ifndef LINUX
#include<process.h>
#endif
#include<errno.h>
#include<math.h>
#include<sys/stat.h>

#include "bgiext.h"
#include "bib_e.h"
#include "rysuj_e.h"
#include "b_mouse.h"
#include "o_loadf.h"
#include "o_protec.h"
#include "b_textw.h"
#include "o_lfile.h"
#include "o_spec.h"
#include "alf_res.h"
#include "o_dialog.h"
#include "o_image.h"
#include "o_pltprn.h"
#include "o_plt.h"
#include "o_prn.h"
#include "o_addmnu.h"
#include "b_bibe.h"
#include "menu.h"

#include "forlinux.h"

#define screen_tip "@x0, y0, dx, dy"

#define ID_ESCAPE         1

extern void disable_F11(void);
extern void enable_F11(void);
extern int PozX, PozY;
extern int PozX0, PozY0;

static GROUP_BOX gr_box_screen[1] =
        {
                { 100, 100, 200, 200,
                  COLOR_NULL ,COLOR_NULL, "Desktop", 0, NULL,
                },
        };

static BUTTON buttons_screen[] =
        {
                { 0, 0, 100, 20, COLOR_NULL,
                  COLOR_NULL, COLOR_NULL, "ESC", 0,B_PUSHBUTTON, 99, 1,BUTTON_HIDDEN, ID_ESCAPE, 0, 0,
                },
        };

static IMAGE images_screen[] =
        {
                { 20,20, 64, 64, -1, screen_tip},
        };


static TDIALOG screen_dlg =
        {
                5, 5, WIDTH_WORLD - 10, HEIGHT_WORLD - 10,COLOR_NULL,COLOR_NULL,COLOR_NULL, COLOR_NULL, 0x20,  0, 0,
                "Dim",
                0, NULL,
                0, NULL,
                0, &gr_box_screen,
                0, NULL,
                1, &images_screen,
                1, &buttons_screen,
                0, NULL,
                0,NULL,
                NULL,
                NULL,
                0,
                0,
                NULL,
        };


static int proc_dlg_screen(int n)
/*------------------------------*/
{
    int ret = Dlg_Ret_Val_Cancel;

    switch (n)
    {
        case ID_ESCAPE:
            ret = Dlg_Ret_Val_Cancel;
            break;
        default:
            ret = Dlg_Ret_Val_Cancel;
            break;
    }
    return ret;
};

int Get_A_Screen(int ret_left_x, int ret_right_x, int ret_top_y, int ret_bottom_y, int mouse_curx, int mouse_cury) {
    int Ret_Val;
    static DLG_COLOR color_dlg;
    double wsp_x, wsp_y;
    int ret;

    screen_dlg.flags = 0x20;
    screen_dlg.SizeGroupT = 0;

    wsp_x = max(1.75 / 9.0 * (float)WIDTH, 1.75);
    wsp_y = max(2.5 / 19.0 * (float)HEIGHT, 2.5);  //15

    screen_dlg.dx = ((float)getmaxx() - 20.0) / wsp_x;
    screen_dlg.dy = ((float)getmaxy() - 42.0 *((float)HEIGHT / 12.0) - 20) / wsp_y;

    screen_dlg.x =  (int)(-6.0  / wsp_x);
    screen_dlg.y = (int)(-(1.5 * ED_INF_HEIGHT + 0.5) / wsp_y);

    buttons_screen[0].x=0;
    buttons_screen[0].y=0;
    buttons_screen[0].dx=ret_right_x-ret_left_x; //screen_dlg.dx;
    buttons_screen[0].dy=ret_bottom_y-ret_top_y; //screen_dlg.dy;

    Get_Default_Color_Dlg(&color_dlg);

    disable_F11();

    PozX = mouse_curx;
    PozY = mouse_cury;

    Ret_Val = Dialog(&screen_dlg, &color_dlg, proc_dlg_screen, bMouse);

    enable_F11();

    return Ret_Val;
}

#undef __O_SCREEN_DLG__