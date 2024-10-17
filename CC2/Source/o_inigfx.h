typedef char	* T_Fstring;
#ifndef BOOL
#define  BOOL   int
#endif
#ifndef TRUE
#define  TRUE   1
#endif
#ifndef FALSE
#define  FALSE  0
#endif


#pragma pack(1)
typedef struct
{
 int gfx_driver;
 int gfx_width;
 int gfx_height;
 int gfx_bpp;
 int gfx_display_switch;
 int gfx_mmx_mode;
 int gfx_refresh;
 double gfx_aspect;
} DRIVER_STRUCT;
#pragma pack()