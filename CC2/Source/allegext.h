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

#include <allegro.h>
#include <loadpng.h>
#ifdef __cplusplus
extern "C" {
#endif
extern     unsigned imagesize(int left, int top, int right, int bottom);
extern     void bar(int left, int top, int right, int bottom);
extern     void moveto(int x, int y);
#ifdef __cplusplus
}
#endif

#define GRXMain main  /* WIN32 targets undef it */

#ifndef NULL
#define NULL		((void *)(0))
#endif

#define COPY_PUT 0
#define XOR_PUT  1
#define OR_PUT   2
#define AND_PUT  3
#define NOT_PUT  4

#define TRANSLUCENCY_PREVIEW 80

#ifndef TRUE
#  define TRUE 1
#endif
#ifndef FALSE
#  define FALSE 0
#endif

#ifndef   BLACK
#  define BLACK         0
#endif
#ifndef   BLUE
#  define BLUE          1
#endif
#ifndef   GREEN
#  define GREEN         2
#endif
#ifndef   CYAN
#  define CYAN          3
#endif
#ifndef   RED
#  define RED           4
#endif
#ifndef MAGENTA
#  define MAGENTA       5
#endif
#ifndef   BROWN
#  define BROWN         6
#endif
#ifndef   LIGHTGRAY
#  define LIGHTGRAY     7
#endif
#ifndef   DARKGRAY
#  define DARKGRAY      8
#endif
#ifndef   LIGHTBLUE
#  define LIGHTBLUE     9
#endif
#ifndef   LIGHTGREEN
#  define LIGHTGREEN   10
#endif
#ifndef   LIGHTCYAN
#  define LIGHTCYAN    11
#endif
#ifndef   LIGHTRED
#  define LIGHTRED     12
#endif
#ifndef   LIGHTMAGENTA
#  define LIGHTMAGENTA 13
#endif
#ifndef   YELLOW
#  define YELLOW       14
#endif
#ifndef   WHITE
#  define WHITE        (__gr_White())
#endif

#define EGA_BLACK        0
#define EGA_BLUE         1
#define EGA_GREEN        2
#define EGA_RED          4
#define EGA_LIGHTBLUE    57
#define EGA_LIGHTGREEN   58
#define EGA_LIGHTRED     60
#define EGA_CYAN         3
#define EGA_LIGHTCYAN    59
#define EGA_MAGENTA      5
#define EGA_LIGHTMAGENTA 61
#define EGA_BROWN        20
#define EGA_LIGHTGRAY    7
#define EGA_DARKGRAY     56
#define EGA_YELLOW       62
#define EGA_WHITE        63

#ifndef near            /* get rid of these stupid keywords */
#define near
#endif
#ifndef far
#define far
#endif
#ifndef huge
#define huge
#endif


#define SOLID_LINE   0
#define DOTTED_LINE  1
#define CENTER_LINE  2
#define DASHED_LINE  3
#define USERBIT_LINE 4

#define NORM_WIDTH   1
#define THICK_WIDTH  3


#define LEFT_TEXT   0
#define CENTER_TEXT 1
#define RIGHT_TEXT  2
#define BOTTOM_TEXT 0
#define TOP_TEXT    2

#define GR_M_MOTION         0x001               /* mouse event flag bits */
#define GR_M_LEFT_DOWN      0x002
#define GR_M_LEFT_UP        0x004
#define GR_M_RIGHT_DOWN     0x008
#define GR_M_RIGHT_UP       0x010
#define GR_M_MIDDLE_DOWN    0x020
#define GR_M_MIDDLE_UP      0x040
#define GR_M_BUTTON_DOWN    (GR_M_LEFT_DOWN | GR_M_MIDDLE_DOWN | GR_M_RIGHT_DOWN)
#define GR_M_BUTTON_UP      (GR_M_LEFT_UP   | GR_M_MIDDLE_UP   | GR_M_RIGHT_UP)
#define GR_M_BUTTON_CHANGE  (GR_M_BUTTON_UP | GR_M_BUTTON_DOWN )

#define GR_M_LEFT           1                   /* mouse button index bits */
#define GR_M_RIGHT          2
#define GR_M_MIDDLE         4

#define GR_M_KEYPRESS       0x080               /* other event flag bits */
#define GR_M_POLL           0x100
#define GR_M_NOPAINT        0x200
#define GR_M_EVENT          (GR_M_MOTION | GR_M_KEYPRESS | GR_M_BUTTON_DOWN | GR_M_BUTTON_UP)

#define GrWRITE         0UL             /* write color */


typedef struct _GR_mouseEvent {                 /* mouse event buffer structure */
	int  flags;                                 /* event type flags (see above) */
	int  x,y;                                   /* mouse coordinates */
	int  buttons;                               /* mouse button state */
	int  key;                                   /* key code from keyboard */
	int  kbstat;                                /* keybd status (ALT, CTRL, etc..) */
	long dtime;                                 /* time since last event (msec) */
} GrMouseEvent;




struct _GR_frame {
	char    far *gf_baseaddr[4];        /* base address of frame memory */
	short   gf_selector;                /* frame memory segment selector */
	char    gf_onscreen;                /* is it in video memory ? */
	char    gf_memflags;                /* memory allocation flags */
	int     gf_lineoffset;              /* offset to next scan line in bytes */
	struct _GR_frameDriver *gf_driver;  /* frame access functions */
};

struct _GR_context {
	struct _GR_frame    gc_frame;       /* frame buffer info */
	struct _GR_context *gc_root;        /* context which owns frame */
	int    gc_xmax;                     /* max X coord (width  - 1) */
	int    gc_ymax;                     /* max Y coord (height - 1) */
	int    gc_xoffset;                  /* X offset from root's base */
	int    gc_yoffset;                  /* Y offset from root's base */
	int    gc_xcliplo;                  /* low X clipping limit */
	int    gc_ycliplo;                  /* low Y clipping limit */
	int    gc_xcliphi;                  /* high X clipping limit */
	int    gc_ycliphi;                  /* high Y clipping limit */
	int    gc_usrxbase;                 /* user window min X coordinate */
	int    gc_usrybase;                 /* user window min Y coordinate */
	int    gc_usrwidth;                 /* user window width  */
	int    gc_usrheight;                /* user window height */
#   define gc_baseaddr                  gc_frame.gf_baseaddr
#   define gc_selector                  gc_frame.gf_selector
#   define gc_onscreen                  gc_frame.gf_onscreen
#   define gc_memflags                  gc_frame.gf_memflags
#   define gc_lineoffset                gc_frame.gf_lineoffset
#   define gc_driver                    gc_frame.gf_driver
};

typedef struct _GR_context      GrContext;

enum fill_patterns {        /* Fill patterns for get/setfillstyle */
	EMPTY_FILL,     /* fills area in background color */
	SOLID_FILL,     /* fills area in solid fill color */
	LINE_FILL,      /* --- fill */
	LTSLASH_FILL,       /* /// fill */
	SLASH_FILL,     /* /// fill with thick lines */
	BKSLASH_FILL,       /* \\\ fill with thick lines */
	LTBKSLASH_FILL,     /* \\\ fill */
	HATCH_FILL,     /* light hatch fill */
	XHATCH_FILL,        /* heavy cross hatch fill */
	INTERLEAVE_FILL,    /* interleaving line fill */
	WIDE_DOT_FILL,      /* Widely spaced dot fill */
	CLOSE_DOT_FILL,     /* Closely spaced dot fill */
	USER_FILL       /* user defined fill */
};


#define HORIZ_DIR   0       /* left to right */
#define VERT_DIR    1       /* bottom to top */


struct viewporttype {
	int left, top, right, bottom;
	int clip;
};

struct textsettingstype {
	int font;
	int direction;
	int charsize;
	int horiz;
	int vert;
};


#ifdef __cplusplus
extern "C" {
#endif

extern int  __gr_color;                /* drawing color       */
extern int getmaxx(void);
extern int getmaxy(void);
#ifdef __cplusplus
}
#endif


#define grOk                0
#define DETECT             (-2)
#define VGAHI              2

