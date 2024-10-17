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

PPOLE pmL_section_UK_si_0_0[] = {
{u8"UA 75x50x5",L' ',0,NULL},
{u8"UA 75x50x6",L' ',0,NULL},
{u8"UA 75x50x8",L' ',0,NULL},
{u8"UA 80x40x6",L' ',0,NULL},
{u8"UA 80x40x8",L' ',0,NULL},
{u8"UA 100x50x6",L' ',0,NULL},
{u8"UA 100x50x8",L' ',0,NULL},
{u8"UA 100x50x10",L' ',0,NULL},
{u8"UA 100x65x7",L' ',0,NULL},
{u8"UA 100x65x8",L' ',0,NULL},
{u8"UA 100x65x10",L' ',0,NULL},
{u8"UA 100x75x8",L' ',0,NULL},
{u8"UA 100x75x10",L' ',0,NULL},
{u8"UA 100x75x12",L' ',0,NULL},
{u8"UA 120x80x8",L' ',0,NULL},
{u8"UA 120x80x10",L' ',0,NULL},
{u8"UA 120x80x12",L' ',0,NULL},
{u8"UA 125x75x8",L' ',0,NULL},
{u8"UA 125x75x10",L' ',0,NULL},
{u8"UA 125x75x12",L' ',0,NULL},
{u8"UA 150x75x10",L' ',0,NULL},
{u8"UA 150x75x12",L' ',0,NULL},
{u8"UA 150x75x15",L' ',0,NULL},
{u8"UA 150x90x10",L' ',0,NULL},
{u8"UA 150x90x12",L' ',0,NULL},
{u8"UA 150x90x15",L' ',0,NULL},
{u8"UA 150x100x10",L' ',0,NULL},
{u8"UA 150x100x12",L' ',0,NULL},
{u8"UA 200x100x10",L' ',0,NULL},
{u8"UA 200x100x12",L' ',0,NULL},
{u8"UA 200x100x15",L' ',0,NULL},
{u8"UA 250x90x10",L' ',0,NULL},
{u8"UA 250x90x12",L' ',0,NULL},
{u8"UA 250x90x14",L' ',0,NULL},
{u8"UA 250x90x16",L' ',0,NULL},
};

PTMENU mL_section_UK_si_0_0 = { 35,0,0,14,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_0_0,NULL,NULL };

PPOLE pmL_section_UK_si_0_1[] = {
{u8"L 150x150x10",L' ',0,NULL},
{u8"L 150x150x12",L' ',0,NULL},
{u8"L 150x150x15",L' ',0,NULL},
{u8"L 150x150x18",L' ',0,NULL},
{u8"L 200x200x16",L' ',0,NULL},
{u8"L 200x200x18",L' ',0,NULL},
{u8"L 200x200x20",L' ',0,NULL},
{u8"L 200x200x24",L' ',0,NULL},
};

PTMENU mL_section_UK_si_0_1 = { 8,0,0,13,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_0_1,NULL,NULL };

PPOLE pmL_section_UK_si_0_2[] = {
{u8"EA 40x40x4",L' ',0,NULL},
{u8"EA 45x45x4.5",L' ',0,NULL},
{u8"EA 50x50x5",L' ',0,NULL},
{u8"EA 60x60x6",L' ',0,NULL},
{u8"EA 65x65x7",L' ',0,NULL},
{u8"EA 70x70x7",L' ',0,NULL},
{u8"EA 75x75x8",L' ',0,NULL},
{u8"EA 80x80x8",L' ',0,NULL},
{u8"EA 90x90x9",L' ',0,NULL},
{u8"EA 100x100x10",L' ',0,NULL},
{u8"EA 110x110x12",L' ',0,NULL},
{u8"EA 120x120x12",L' ',0,NULL},
{u8"EA 125x125x12",L' ',0,NULL},
{u8"EA 130x130x12",L' ',0,NULL},
{u8"EA 140x140x13",L' ',0,NULL},
{u8"EA 150x150x15",L' ',0,NULL},
{u8"EA 160x160x15",L' ',0,NULL},
{u8"EA 175x175x15",L' ',0,NULL},
{u8"EA 180x180x18",L' ',0,NULL},
{u8"EA 200x200x20",L' ',0,NULL},
{u8"EA 250x250x28",L' ',0,NULL},
};

PTMENU mL_section_UK_si_0_2 = { 21,0,0,14,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_0_2,NULL,NULL };

PPOLE pmL_section_UK_si_0_3[] = {
{u8"UKA 90x7",L' ',0,NULL},
{u8"UKA 90x8",L' ',0,NULL},
{u8"UKA 90x10",L' ',0,NULL},
{u8"UKA 90x12",L' ',0,NULL},
{u8"UKA 100x8",L' ',0,NULL},
{u8"UKA 100x10",L' ',0,NULL},
{u8"UKA 100x12",L' ',0,NULL},
{u8"UKA 100x15",L' ',0,NULL},
{u8"UKA 120x8",L' ',0,NULL},
{u8"UKA 120x10",L' ',0,NULL},
{u8"UKA 120x12",L' ',0,NULL},
{u8"UKA 120x15",L' ',0,NULL},
{u8"UKA 150x10",L' ',0,NULL},
{u8"UKA 150x12",L' ',0,NULL},
{u8"UKA 150x15",L' ',0,NULL},
{u8"UKA 150x18",L' ',0,NULL},
{u8"UKA 200x16",L' ',0,NULL},
{u8"UKA 200x18",L' ',0,NULL},
{u8"UKA 200x20",L' ',0,NULL},
{u8"UKA 200x24",L' ',0,NULL},
};

PTMENU mL_section_UK_si_0_3 = { 20,0,0,11,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_0_3,NULL,NULL };

PPOLE pmL_section_UK_si_0_4[] = {
{u8"UKA 100x65x7",L' ',0,NULL},
{u8"UKA 100x65x8",L' ',0,NULL},
{u8"UKA 100x65x10",L' ',0,NULL},
{u8"UKA 100x75x8",L' ',0,NULL},
{u8"UKA 100x75x10",L' ',0,NULL},
{u8"UKA 100x75x12",L' ',0,NULL},
{u8"UKA 125x75x8",L' ',0,NULL},
{u8"UKA 125x75x10",L' ',0,NULL},
{u8"UKA 125x75x12",L' ',0,NULL},
{u8"UKA 150x75x10",L' ',0,NULL},
{u8"UKA 150x75x12",L' ',0,NULL},
{u8"UKA 150x75x15",L' ',0,NULL},
{u8"UKA 150x90x10",L' ',0,NULL},
{u8"UKA 150x90x12",L' ',0,NULL},
{u8"UKA 150x90x15",L' ',0,NULL},
{u8"UKA 200x100x10",L' ',0,NULL},
{u8"UKA 200x100x12",L' ',0,NULL},
{u8"UKA 200x100x15",L' ',0,NULL},
{u8"UKA 200x150x12",L' ',0,NULL},
{u8"UKA 200x150x15",L' ',0,NULL},
{u8"UKA 200x150x18",L' ',0,NULL},
};

PTMENU mL_section_UK_si_0_4 = { 21,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_0_4,NULL,NULL };

PPOLE pmL_section_UK_si_1_0[] = {
{u8"L 20x20x3.0",L' ',0,NULL},
{u8"L 25x25x3.0",L' ',0,NULL},
{u8"L 25x25x4.0",L' ',0,NULL},
{u8"L 30x30x3.0",L' ',0,NULL},
{u8"L 30x30x4.0",L' ',0,NULL},
{u8"L 35x35x4.0",L' ',0,NULL},
{u8"L 40x40x4.0",L' ',0,NULL},
{u8"L 40x40x5.0",L' ',0,NULL},
{u8"L 45x45x4.5",L' ',0,NULL},
{u8"L 50x50x4.0",L' ',0,NULL},
{u8"L 50x50x5.0",L' ',0,NULL},
{u8"L 50x50x6.0",L' ',0,NULL},
{u8"L 60x60x5.0",L' ',0,NULL},
{u8"L 60x60x6.0",L' ',0,NULL},
{u8"L 60x60x8.0",L' ',0,NULL},
{u8"L 65x65x7.0",L' ',0,NULL},
{u8"L 70x70x6.0",L' ',0,NULL},
{u8"L 70x70x7.0",L' ',0,NULL},
{u8"L 75x75x6.0",L' ',0,NULL},
{u8"L 75x75x8.0",L' ',0,NULL},
{u8"L 80x80x8.0",L' ',0,NULL},
{u8"L 80x80x10.0",L' ',0,NULL},
{u8"L 90x90x7.0",L' ',0,NULL},
{u8"L 90x90x8.0",L' ',0,NULL},
{u8"L 90x90x10.0",L' ',0,NULL},
{u8"L 90x90x12.0",L' ',0,NULL},
{u8"L 100x100x8.0",L' ',0,NULL},
{u8"L 100x100x10.0",L' ',0,NULL},
{u8"L 100x100x12.0",L' ',0,NULL},
{u8"L 100x100x15.0",L' ',0,NULL},
{u8"L 120x120x8.0",L' ',0,NULL},
{u8"L 120x120x10.0",L' ',0,NULL},
{u8"L 120x120x12.0",L' ',0,NULL},
{u8"L 120x120x15.0",L' ',0,NULL},
{u8"L 150x150x10.0",L' ',0,NULL},
{u8"L 150x150x12.0",L' ',0,NULL},
{u8"L 150x150x15.0",L' ',0,NULL},
{u8"L 150x150x18.0",L' ',0,NULL},
{u8"L 200x200x16.0",L' ',0,NULL},
{u8"L 200x200x18.0",L' ',0,NULL},
{u8"L 200x200x20.0",L' ',0,NULL},
{u8"L 200x200x24.0",L' ',0,NULL},
};

PTMENU mL_section_UK_si_1_0 = { 42,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_1_0,NULL,NULL };

PPOLE pmL_section_UK_si_1_1[] = {
{u8"L 30x20x3.0",L' ',0,NULL},
{u8"L 30x20x4.0",L' ',0,NULL},
{u8"L 40x20x4.0",L' ',0,NULL},
{u8"L 40x25x4.0",L' ',0,NULL},
{u8"L 45x30x4.0",L' ',0,NULL},
{u8"L 50x30x5.0",L' ',0,NULL},
{u8"L 60x30x5.0",L' ',0,NULL},
{u8"L 60x40x5.0",L' ',0,NULL},
{u8"L 60x40x6.0",L' ',0,NULL},
{u8"L 65x50x5.0",L' ',0,NULL},
{u8"L 70x50x6.0",L' ',0,NULL},
{u8"L 75x50x6.0",L' ',0,NULL},
{u8"L 75x50x8.0",L' ',0,NULL},
{u8"L 80x40x6.0",L' ',0,NULL},
{u8"L 80x40x8.0",L' ',0,NULL},
{u8"L 80x60x7.0",L' ',0,NULL},
{u8"L 100x50x6.0",L' ',0,NULL},
{u8"L 100x50x8.0",L' ',0,NULL},
{u8"L 100x65x7.0",L' ',0,NULL},
{u8"L 100x65x8.0",L' ',0,NULL},
{u8"L 100x65x10.0",L' ',0,NULL},
{u8"L 100x75x8.0",L' ',0,NULL},
{u8"L 100x75x10.0",L' ',0,NULL},
{u8"L 100x75x12.0",L' ',0,NULL},
{u8"L 125x75x8.0",L' ',0,NULL},
{u8"L 125x75x10.0",L' ',0,NULL},
{u8"L 125x75x12.0",L' ',0,NULL},
{u8"L 150x75x10.0",L' ',0,NULL},
{u8"L 150x75x12.0",L' ',0,NULL},
{u8"L 150x75x15.0",L' ',0,NULL},
{u8"L 150x90x10.0",L' ',0,NULL},
{u8"L 150x90x12.0",L' ',0,NULL},
{u8"L 150x90x15.0",L' ',0,NULL},
{u8"L 200x100x10.0",L' ',0,NULL},
{u8"L 200x100x12.0",L' ',0,NULL},
{u8"L 200x100x15.0",L' ',0,NULL},
{u8"L 200x150x12.0",L' ',0,NULL},
{u8"L 200x150x15.0",L' ',0,NULL},
{u8"L 200x150x18.0",L' ',0,NULL},
};

PTMENU mL_section_UK_si_1_1 = { 39,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmL_section_UK_si_1_1,NULL,NULL };

