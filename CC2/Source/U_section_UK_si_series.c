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

PPOLE pmU_section_UK_si_0_0[] = {
{u8"TFC 76x38",L' ',0,NULL},
{u8"TFC 100x50",L' ',0,NULL},
{u8"TFC 120x55",L' ',0,NULL},
{u8"TFC 127x64",L' ',0,NULL},
{u8"TFC 140x60",L' ',0,NULL},
{u8"TFC 152x76",L' ',0,NULL},
{u8"TFC 160x65",L' ',0,NULL},
{u8"TFC 178x54",L' ',0,NULL},
{u8"TFC 180x70",L' ',0,NULL},
{u8"TFC 200x75",L' ',0,NULL},
};

PTMENU mU_section_UK_si_0_0 = { 10,0,0,11,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_0_0,NULL,NULL };

PPOLE pmU_section_UK_si_0_1[] = {
{u8"SCP 100x50x10.2",L' ',0,NULL},
{u8"SCP 125x65x14.8",L' ',0,NULL},
{u8"SCP 150x75x17.9",L' ',0,NULL},
{u8"SCP 150x90x23.9",L' ',0,NULL},
{u8"SCP 180x75x20.3",L' ',0,NULL},
{u8"SCP 180x90x26.1",L' ',0,NULL},
{u8"SCP 200x75x23.4",L' ',0,NULL},
{u8"SCP 200x90x29.7",L' ',0,NULL},
{u8"SCP 230x75x25.7",L' ',0,NULL},
{u8"SCP 230x90x32.2",L' ',0,NULL},
{u8"SCP 250x90x35.5",L' ',0,NULL},
{u8"SCP 260x75x27.6",L' ',0,NULL},
{u8"SCP 260x90x34.8",L' ',0,NULL},
{u8"SCP 300x90x41.4",L' ',0,NULL},
{u8"SCP 300x100x45.5",L' ',0,NULL},
{u8"SCP 380x100x54.0",L' ',0,NULL},
{u8"SCP 430x100x64.4",L' ',0,NULL},
};

PTMENU mU_section_UK_si_0_1 = { 17,0,0,17,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_0_1,NULL,NULL };

PPOLE pmU_section_UK_si_0_2[] = {
{u8"SC 50x25x3.9",L' ',0,NULL},
{u8"SC 75x40x6.9",L' ',0,NULL},
{u8"SC 100x50x9.3",L' ',0,NULL},
{u8"SC 125x65x13.4",L' ',0,NULL},
{u8"SC 150x75x18.6",L' ',0,NULL},
{u8"SC 150x75x24",L' ',0,NULL},
{u8"SC 180x75x21.4",L' ',0,NULL},
{u8"SC 200x80x24.6",L' ',0,NULL},
{u8"SC 200x90x30.3",L' ',0,NULL},
{u8"SC 230x80x28.4",L' ',0,NULL},
{u8"SC 250x90x34.6",L' ',0,NULL},
{u8"SC 250x90x40.2",L' ',0,NULL},
{u8"SC 300x90x38.1",L' ',0,NULL},
{u8"SC 300x90x43.8",L' ',0,NULL},
{u8"SC 300x90x48.6",L' ',0,NULL},
{u8"SC 380x100x54.5",L' ',0,NULL},
{u8"SC 380x100x62.0",L' ',0,NULL},
{u8"SC 380x100x67.3",L' ',0,NULL},
};

PTMENU mU_section_UK_si_0_2 = { 18,0,0,16,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_0_2,NULL,NULL };

PPOLE pmU_section_UK_si_0_3[] = {
{u8"CH 76x38x7",L' ',0,NULL},
{u8"CH 102x51x10",L' ',0,NULL},
{u8"CH 127x64x15",L' ',0,NULL},
{u8"CH 152x76x18",L' ',0,NULL},
{u8"CH 152x89x24",L' ',0,NULL},
{u8"CH 178x76x21",L' ',0,NULL},
{u8"CH 178x89x27",L' ',0,NULL},
{u8"CH 203x76x24",L' ',0,NULL},
{u8"CH 203x89x30",L' ',0,NULL},
{u8"CH 229x76x26",L' ',0,NULL},
{u8"CH 229x89x33",L' ',0,NULL},
{u8"CH 254x76x28",L' ',0,NULL},
{u8"CH 254x89x36",L' ',0,NULL},
{u8"CH 305x89x42",L' ',0,NULL},
{u8"CH 305x102x46",L' ',0,NULL},
{u8"CH 381x102x55",L' ',0,NULL},
{u8"CH 432x102x65",L' ',0,NULL},
};

PTMENU mU_section_UK_si_0_3 = { 17,0,0,14,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_0_3,NULL,NULL };

PPOLE pmU_section_UK_si_1_0[] = {
{u8"PFC 100x50x10",L' ',0,NULL},
{u8"PFC 125x65x15",L' ',0,NULL},
{u8"PFC 150x75x18",L' ',0,NULL},
{u8"PFC 150x90x24",L' ',0,NULL},
{u8"PFC 180x75x20",L' ',0,NULL},
{u8"PFC 180x90x26",L' ',0,NULL},
{u8"PFC 200x75x23",L' ',0,NULL},
{u8"PFC 200x90x30",L' ',0,NULL},
{u8"PFC 230x75x26",L' ',0,NULL},
{u8"PFC 230x90x32",L' ',0,NULL},
{u8"PFC 260x75x28",L' ',0,NULL},
{u8"PFC 260x90x35",L' ',0,NULL},
{u8"PFC 300x90x41",L' ',0,NULL},
{u8"PFC 300x100x46",L' ',0,NULL},
};

PTMENU mU_section_UK_si_1_0 = { 14,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_1_0,NULL,NULL };

PPOLE pmU_section_UK_si_1_1[] = {
{u8"PFC 100x50x10",L' ',0,NULL},
{u8"PFC 125x65x15",L' ',0,NULL},
{u8"PFC 150x75x18",L' ',0,NULL},
{u8"PFC 150x90x24",L' ',0,NULL},
{u8"PFC 180x75x20",L' ',0,NULL},
{u8"PFC 180x90x26",L' ',0,NULL},
{u8"PFC 200x75x23",L' ',0,NULL},
{u8"PFC 200x90x30",L' ',0,NULL},
{u8"PFC 230x75x26",L' ',0,NULL},
{u8"PFC 230x90x32",L' ',0,NULL},
{u8"PFC 260x75x28",L' ',0,NULL},
{u8"PFC 260x90x35",L' ',0,NULL},
{u8"PFC 300x90x41",L' ',0,NULL},
{u8"PFC 300x100x46",L' ',0,NULL},
{u8"PFC 380x100x54",L' ',0,NULL},
{u8"PFC 430x100x64",L' ',0,NULL},
};

PTMENU mU_section_UK_si_1_1 = { 16,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_1_1,NULL,NULL };

PPOLE pmU_section_UK_si_1_2[] = {
{u8"PFC 150X75X5.5X10",L' ',0,NULL},
{u8"PFC 200X75X6X12.5",L' ',0,NULL},
};

PTMENU mU_section_UK_si_1_2 = { 2,0,0,18,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_1_2,NULL,NULL };

PPOLE pmU_section_UK_si_1_3[] = {
{u8"UKPFC 100x50x10",L' ',0,NULL},
{u8"UKPFC 125x65x15",L' ',0,NULL},
{u8"UKPFC 150x75x18",L' ',0,NULL},
{u8"UKPFC 150x90x24",L' ',0,NULL},
{u8"UKPFC 180x75x20",L' ',0,NULL},
{u8"UKPFC 180x90x26",L' ',0,NULL},
{u8"UKPFC 200x75x23",L' ',0,NULL},
{u8"UKPFC 200x90x30",L' ',0,NULL},
{u8"UKPFC 230x75x26",L' ',0,NULL},
{u8"UKPFC 230x90x32",L' ',0,NULL},
{u8"UKPFC 260x75x28",L' ',0,NULL},
{u8"UKPFC 260x90x35",L' ',0,NULL},
{u8"UKPFC 300x90x41",L' ',0,NULL},
{u8"UKPFC 300x100x46",L' ',0,NULL},
{u8"UKPFC 380x100x54",L' ',0,NULL},
{u8"UKPFC 430x100x64",L' ',0,NULL},
};

PTMENU mU_section_UK_si_1_3 = { 16,0,0,17,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_1_3,NULL,NULL };

PPOLE pmU_section_UK_si_2_0[] = {
{u8"TFC 76x38x7",L' ',0,NULL},
};

PTMENU mU_section_UK_si_2_0 = { 1,0,0,12,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_2_0,NULL,NULL };

PPOLE pmU_section_UK_si_3_0[] = {
{u8"PFC 100x50x10",L' ',0,NULL},
{u8"PFC 125x65x15",L' ',0,NULL},
{u8"PFC 150x75x18",L' ',0,NULL},
{u8"PFC 150x90x24",L' ',0,NULL},
{u8"PFC 180x75x20",L' ',0,NULL},
{u8"PFC 180x90x26",L' ',0,NULL},
{u8"PFC 200x75x23",L' ',0,NULL},
{u8"PFC 200x90x30",L' ',0,NULL},
{u8"PFC 230x75x26",L' ',0,NULL},
{u8"PFC 230x90x32",L' ',0,NULL},
{u8"PFC 260x75x28",L' ',0,NULL},
{u8"PFC 260x90x35",L' ',0,NULL},
{u8"PFC 300x90x41",L' ',0,NULL},
{u8"PFC 300x100x46",L' ',0,NULL},
{u8"PFC 380x100x54",L' ',0,NULL},
{u8"PFC 430x100x64",L' ',0,NULL},
};

PTMENU mU_section_UK_si_3_0 = { 16,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_UK_si_3_0,NULL,NULL };

