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

PPOLE pmU_section_EU_si_0_0[] = {
{u8"PFC 100x50",L' ',0,NULL},
{u8"PFC 180x70",L' ',0,NULL},
{u8"PFC 200x75",L' ',0,NULL},
{u8"PFC 230x90",L' ',0,NULL},
{u8"PFC 260x90",L' ',0,NULL},
{u8"PFC 300x100",L' ',0,NULL},
};

PTMENU mU_section_EU_si_0_0 = { 6,0,0,12,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_EU_si_0_0,NULL,NULL };

PPOLE pmU_section_EU_si_1_0[] = {
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

PTMENU mU_section_EU_si_1_0 = { 16,0,0,15,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_EU_si_1_0,NULL,NULL };

PPOLE pmU_section_EU_si_1_1[] = {
{u8"UPE 80",L' ',0,NULL},
{u8"UPE 100",L' ',0,NULL},
{u8"UPE 120",L' ',0,NULL},
{u8"UPE 140",L' ',0,NULL},
{u8"UPE 160",L' ',0,NULL},
{u8"UPE 180",L' ',0,NULL},
{u8"UPE 200",L' ',0,NULL},
{u8"UPE 220",L' ',0,NULL},
{u8"UPE 240",L' ',0,NULL},
{u8"UPE 270",L' ',0,NULL},
{u8"UPE 300",L' ',0,NULL},
{u8"UPE 330",L' ',0,NULL},
{u8"UPE 360",L' ',0,NULL},
{u8"UPE 400",L' ',0,NULL},
};

PTMENU mU_section_EU_si_1_1 = { 14,0,0,8,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_EU_si_1_1,NULL,NULL };

PPOLE pmU_section_EU_si_1_2[] = {
{u8"UPN 50",L' ',0,NULL},
{u8"UPN 65",L' ',0,NULL},
{u8"UPN 80",L' ',0,NULL},
{u8"UPN 100",L' ',0,NULL},
{u8"UPN 120",L' ',0,NULL},
{u8"UPN 140",L' ',0,NULL},
{u8"UPN 160",L' ',0,NULL},
{u8"UPN 180",L' ',0,NULL},
{u8"UPN 200",L' ',0,NULL},
{u8"UPN 220",L' ',0,NULL},
{u8"UPN 240",L' ',0,NULL},
{u8"UPN 260",L' ',0,NULL},
{u8"UPN 280",L' ',0,NULL},
{u8"UPN 300",L' ',0,NULL},
{u8"UPN 320",L' ',0,NULL},
{u8"UPN 350",L' ',0,NULL},
{u8"UPN 380",L' ',0,NULL},
{u8"UPN 400",L' ',0,NULL},
};

PTMENU mU_section_EU_si_1_2 = { 18,0,0,8,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmU_section_EU_si_1_2,NULL,NULL };

