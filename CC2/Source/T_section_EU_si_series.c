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

#include <stdio.h>
#include <forwin.h>
#include "bib_e.h"

PPOLE pmT_section_EU_si_0_0[] = {
{u8"1/2 HEB 140",L' ',0,NULL},
{u8"1/2 HEB 160",L' ',0,NULL},
{u8"1/2 HEB 180",L' ',0,NULL},
{u8"1/2 HEB 200",L' ',0,NULL},
{u8"1/2 HEB 220",L' ',0,NULL},
{u8"1/2 HEB 240",L' ',0,NULL},
{u8"1/2 HEB 260",L' ',0,NULL},
{u8"1/2 HEB 280",L' ',0,NULL},
{u8"1/2 HEB 300",L' ',0,NULL},
{u8"1/2 HEB 320",L' ',0,NULL},
{u8"1/2 HEB 340",L' ',0,NULL},
{u8"1/2 HEB 360",L' ',0,NULL},
{u8"1/2 HEB 400",L' ',0,NULL},
{u8"1/2 HEB 450",L' ',0,NULL},
{u8"1/2 HEB 500",L' ',0,NULL},
{u8"1/2 HEB 550",L' ',0,NULL},
{u8"1/2 HEB 600",L' ',0,NULL},
{u8"1/2 HEB 650",L' ',0,NULL},
{u8"1/2 HEB 700",L' ',0,NULL},
{u8"1/2 HEB 800",L' ',0,NULL},
{u8"1/2 HEB 900",L' ',0,NULL},
{u8"1/2 HEB 1000",L' ',0,NULL},
};

PTMENU mT_section_EU_si_0_0 = { 22,0,0,13,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmT_section_EU_si_0_0,NULL,NULL };

PPOLE pmT_section_EU_si_1_0[] = {
{u8"1/2 HEA 140",L' ',0,NULL},
{u8"1/2 HEA 160",L' ',0,NULL},
{u8"1/2 HEA 180",L' ',0,NULL},
{u8"1/2 HEA 200",L' ',0,NULL},
{u8"1/2 HEA 220",L' ',0,NULL},
{u8"1/2 HEA 240",L' ',0,NULL},
{u8"1/2 HEA 260",L' ',0,NULL},
{u8"1/2 HEA 280",L' ',0,NULL},
{u8"1/2 HEA 300",L' ',0,NULL},
{u8"1/2 HEA 320",L' ',0,NULL},
{u8"1/2 HEA 340",L' ',0,NULL},
{u8"1/2 HEA 360",L' ',0,NULL},
{u8"1/2 HEA 400",L' ',0,NULL},
{u8"1/2 HEA 450",L' ',0,NULL},
{u8"1/2 HEA 500",L' ',0,NULL},
{u8"1/2 HEA 550",L' ',0,NULL},
{u8"1/2 HEA 600",L' ',0,NULL},
{u8"1/2 HEA 650",L' ',0,NULL},
{u8"1/2 HEA 700",L' ',0,NULL},
{u8"1/2 HEA 800",L' ',0,NULL},
{u8"1/2 HEA 900",L' ',0,NULL},
{u8"1/2 HEA 1000",L' ',0,NULL},
};

PTMENU mT_section_EU_si_1_0 = { 22,0,0,13,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmT_section_EU_si_1_0,NULL,NULL };

PPOLE pmT_section_EU_si_2_0[] = {
{u8"1/2 HEM 140",L' ',0,NULL},
{u8"1/2 HEM 160",L' ',0,NULL},
{u8"1/2 HEM 180",L' ',0,NULL},
{u8"1/2 HEM 200",L' ',0,NULL},
{u8"1/2 HEM 220",L' ',0,NULL},
{u8"1/2 HEM 240",L' ',0,NULL},
{u8"1/2 HEM 260",L' ',0,NULL},
{u8"1/2 HEM 280",L' ',0,NULL},
{u8"1/2 HEM 320/305",L' ',0,NULL},
{u8"1/2 HEM 300",L' ',0,NULL},
{u8"1/2 HEM 320",L' ',0,NULL},
{u8"1/2 HEM 340",L' ',0,NULL},
{u8"1/2 HEM 360",L' ',0,NULL},
{u8"1/2 HEM 400",L' ',0,NULL},
{u8"1/2 HEM 450",L' ',0,NULL},
{u8"1/2 HEM 500",L' ',0,NULL},
{u8"1/2 HEM 550",L' ',0,NULL},
{u8"1/2 HEM 600",L' ',0,NULL},
{u8"1/2 HEM 650",L' ',0,NULL},
{u8"1/2 HEM 700",L' ',0,NULL},
{u8"1/2 HEM 800",L' ',0,NULL},
{u8"1/2 HEM 900",L' ',0,NULL},
};

PTMENU mT_section_EU_si_2_0 = { 22,0,0,16,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmT_section_EU_si_2_0,NULL,NULL };

PPOLE pmT_section_EU_si_3_0[] = {
{u8"1/2 IPE 140",L' ',0,NULL},
{u8"1/2 IPE 160",L' ',0,NULL},
{u8"1/2 IPE 180",L' ',0,NULL},
{u8"1/2 IPE 200",L' ',0,NULL},
{u8"1/2 IPE 220",L' ',0,NULL},
{u8"1/2 IPE 240",L' ',0,NULL},
{u8"1/2 IPE 270",L' ',0,NULL},
{u8"1/2 IPE 300",L' ',0,NULL},
{u8"1/2 IPE 330",L' ',0,NULL},
{u8"1/2 IPE 360",L' ',0,NULL},
{u8"1/2 IPE 400",L' ',0,NULL},
{u8"1/2 IPE 450",L' ',0,NULL},
{u8"1/2 IPE 500",L' ',0,NULL},
{u8"1/2 IPE 550",L' ',0,NULL},
{u8"1/2 IPE 600",L' ',0,NULL},
};

PTMENU mT_section_EU_si_3_0 = { 15,0,0,12,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmT_section_EU_si_3_0,NULL,NULL };

PPOLE pmT_section_EU_si_4_0[] = {
{u8"TPH 50",L' ',0,NULL},
{u8"TPH 60",L' ',0,NULL},
{u8"TPH 70",L' ',0,NULL},
{u8"TPH 80",L' ',0,NULL},
{u8"TPH 90",L' ',0,NULL},
{u8"TPH 100",L' ',0,NULL},
{u8"TPH 120",L' ',0,NULL},
{u8"TPH 140",L' ',0,NULL},
};

PTMENU mT_section_EU_si_4_0 = { 8,0,0,8,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmT_section_EU_si_4_0,NULL,NULL };

PPOLE pmT_section_EU_si_5_0[] = {
{u8"T 20x20",L' ',0,NULL},
{u8"T 25x25",L' ',0,NULL},
{u8"T 30x30",L' ',0,NULL},
{u8"T 35x35",L' ',0,NULL},
{u8"T 40x40",L' ',0,NULL},
{u8"T 45x45",L' ',0,NULL},
{u8"T 50x50",L' ',0,NULL},
{u8"T 60x60",L' ',0,NULL},
{u8"T 70x70",L' ',0,NULL},
{u8"T 80x80",L' ',0,NULL},
{u8"T 90x90",L' ',0,NULL},
{u8"T 100x100",L' ',0,NULL},
{u8"T 120x120",L' ',0,NULL},
{u8"T 140x140",L' ',0,NULL},
};

PTMENU mT_section_EU_si_5_0 = { 14,0,0,10,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmT_section_EU_si_5_0,NULL,NULL };

