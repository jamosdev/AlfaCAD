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

PPOLE pmZ_section_US_si_0_0[] = {
{u8"Z 1 3/4 x 1 3/4 x 1.09",L' ',0,NULL},
{u8"Z 2 x 1 1/4 x 0.922",L' ',0,NULL},
{u8"Z 2 3/8 x 1 1/4 x 1.00",L' ',0,NULL},
{u8"Z 3 x 2 11/16 x 2.33",L' ',0,NULL},
{u8"Z 3 x 2 11/16 x 3.38",L' ',0,NULL},
{u8"Z 4 x 3 1/16 x 2.85",L' ',0,NULL},
{u8"Z 4 1/16 x 3 1/8 x 3.57",L' ',0,NULL},
{u8"Z 4 1/8 x 3 3/16 x 4.32",L' ',0,NULL},
{u8"Z 4 x 3 1/16 x 4.78",L' ',0,NULL},
{u8"Z 4 1/8 x 3 3/16 x 6.22",L' ',0,NULL},
{u8"Z 5 x 3 1/4 x 4.01",L' ',0,NULL},
{u8"Z 5 1/16 x 3 5/16 x 4.84",L' ',0,NULL},
{u8"Z 5 x 3 1/4 x 6.19",L' ',0,NULL},
};

PTMENU mZ_section_US_si_0_0 = { 13,0,0,25,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmZ_section_US_si_0_0,NULL,NULL };

PPOLE pmZ_section_US_si_1_0[] = {
{u8"Z 1 3/4 x 1 3/4 x 1.09",L' ',0,NULL},
{u8"Z 2 x 1 1/4 x 0.922",L' ',0,NULL},
{u8"Z 2 3/8 x 1 1/4 x 1.00",L' ',0,NULL},
{u8"Z 3 x 2 11/16 x 2.33",L' ',0,NULL},
{u8"Z 3 x 2 11/16 x 3.38",L' ',0,NULL},
{u8"Z 4 x 3 1/16 x 2.85",L' ',0,NULL},
{u8"Z 4 1/16 x 3 1/8 x 3.57",L' ',0,NULL},
{u8"Z 4 1/8 x 3 3/16 x 4.32",L' ',0,NULL},
{u8"Z 4 x 3 1/16 x 4.78",L' ',0,NULL},
{u8"Z 4 1/8 x 3 3/16 x 6.22",L' ',0,NULL},
{u8"Z 5 x 3 1/4 x 4.01",L' ',0,NULL},
{u8"Z 5 1/16 x 3 5/16 x 4.84",L' ',0,NULL},
{u8"Z 5 x 3 1/4 x 6.19",L' ',0,NULL},
};

PTMENU mZ_section_US_si_1_0 = { 13,0,0,25,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmZ_section_US_si_1_0,NULL,NULL };

PPOLE pmZ_section_US_si_2_0[] = {
{u8"CF 8ZU1.25x105",L' ',0,NULL},
{u8"CF 8ZU1.25x090",L' ',0,NULL},
{u8"CF 8ZU1.25x075",L' ',0,NULL},
{u8"CF 8ZU1.25x060",L' ',0,NULL},
{u8"CF 8ZU1.25x048",L' ',0,NULL},
{u8"CF 6ZU1.25x105",L' ',0,NULL},
{u8"CF 6ZU1.25x090",L' ',0,NULL},
{u8"CF 6ZU1.25x075",L' ',0,NULL},
{u8"CF 6ZU1.25x060",L' ',0,NULL},
{u8"CF 6ZU1.25x048",L' ',0,NULL},
{u8"CF 4ZU1.25x090",L' ',0,NULL},
{u8"CF 4ZU1.25x075",L' ',0,NULL},
{u8"CF 4ZU1.25x060",L' ',0,NULL},
{u8"CF 4ZU1.25x048",L' ',0,NULL},
{u8"CF 4ZU1.25x036",L' ',0,NULL},
{u8"CF 3.625ZU1.25x090",L' ',0,NULL},
{u8"CF 3.625ZU1.25x075",L' ',0,NULL},
{u8"CF 3.625ZU1.25x060",L' ',0,NULL},
{u8"CF 3.625ZU1.25x048",L' ',0,NULL},
{u8"CF 3.625ZU1.25x036",L' ',0,NULL},
{u8"CF 2.5ZU1.25x090",L' ',0,NULL},
{u8"CF 2.5ZU1.25x075",L' ',0,NULL},
{u8"CF 2.5ZU1.25x060",L' ',0,NULL},
{u8"CF 2.5ZU1.25x048",L' ',0,NULL},
{u8"CF 2.5ZU1.25x036",L' ',0,NULL},
{u8"CF 1.5ZU1.25x090",L' ',0,NULL},
{u8"CF 1.5ZU1.25x075",L' ',0,NULL},
{u8"CF 1.5ZU1.25x060",L' ',0,NULL},
{u8"CF 1.5ZU1.25x048",L' ',0,NULL},
{u8"CF 1.5ZU1.25x036",L' ',0,NULL},
};

PTMENU mZ_section_US_si_2_0 = { 30,0,0,19,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmZ_section_US_si_2_0,NULL,NULL };

PPOLE pmZ_section_US_si_2_1[] = {
{u8"CF 12ZS3.25x105",L' ',0,NULL},
{u8"CF 12ZS3.25x085",L' ',0,NULL},
{u8"CF 12ZS3.25x070",L' ',0,NULL},
{u8"CF 12ZS2.75x105",L' ',0,NULL},
{u8"CF 12ZS2.75x085",L' ',0,NULL},
{u8"CF 12ZS2.75x070",L' ',0,NULL},
{u8"CF 12ZS2.25x105",L' ',0,NULL},
{u8"CF 12ZS2.25x085",L' ',0,NULL},
{u8"CF 12ZS2.25x070",L' ',0,NULL},
{u8"CF 10ZS3.25x105",L' ',0,NULL},
{u8"CF 10ZS3.25x085",L' ',0,NULL},
{u8"CF 10ZS3.25x070",L' ',0,NULL},
{u8"CF 10ZS3.25x065",L' ',0,NULL},
{u8"CF 10ZS3.25x059",L' ',0,NULL},
{u8"CF 10ZS2.75x105",L' ',0,NULL},
{u8"CF 10ZS2.75x085",L' ',0,NULL},
{u8"CF 10ZS2.75x070",L' ',0,NULL},
{u8"CF 10ZS2.75x065",L' ',0,NULL},
{u8"CF 10ZS2.75x059",L' ',0,NULL},
{u8"CF 10ZS2.25x105",L' ',0,NULL},
{u8"CF 10ZS2.25x085",L' ',0,NULL},
{u8"CF 10ZS2.25x070",L' ',0,NULL},
{u8"CF 10ZS2.25x065",L' ',0,NULL},
{u8"CF 10ZS2.25x059",L' ',0,NULL},
{u8"CF 9ZS2.25x105",L' ',0,NULL},
{u8"CF 9ZS2.25x085",L' ',0,NULL},
{u8"CF 9ZS2.25x070",L' ',0,NULL},
{u8"CF 9ZS2.25x065",L' ',0,NULL},
{u8"CF 9ZS2.25x059",L' ',0,NULL},
{u8"CF 8ZS3.25x105",L' ',0,NULL},
{u8"CF 8ZS3.25x085",L' ',0,NULL},
{u8"CF 8ZS3.25x070",L' ',0,NULL},
{u8"CF 8ZS3.25x065",L' ',0,NULL},
{u8"CF 8ZS3.25x059",L' ',0,NULL},
{u8"CF 8ZS2.75x105",L' ',0,NULL},
{u8"CF 8ZS2.75x085",L' ',0,NULL},
{u8"CF 8ZS2.75x070",L' ',0,NULL},
{u8"CF 8ZS2.75x065",L' ',0,NULL},
{u8"CF 8ZS2.75x059",L' ',0,NULL},
{u8"CF 8ZS2.25x105",L' ',0,NULL},
{u8"CF 8ZS2.25x085",L' ',0,NULL},
{u8"CF 8ZS2.25x070",L' ',0,NULL},
{u8"CF 8ZS2.25x065",L' ',0,NULL},
{u8"CF 8ZS2.25x059",L' ',0,NULL},
{u8"CF 7ZS2.25x105",L' ',0,NULL},
{u8"CF 7ZS2.25x085",L' ',0,NULL},
{u8"CF 7ZS2.25x070",L' ',0,NULL},
{u8"CF 7ZS2.25x065",L' ',0,NULL},
{u8"CF 7ZS2.25x059",L' ',0,NULL},
{u8"CF 6ZS1.25x105",L' ',0,NULL},
{u8"CF 6ZS2.25x085",L' ',0,NULL},
{u8"CF 6ZS2.25x070",L' ',0,NULL},
{u8"CF 6ZS2.25x065",L' ',0,NULL},
{u8"CF 6ZS2.25x059",L' ',0,NULL},
{u8"CF 4ZS2.25x070",L' ',0,NULL},
{u8"CF 4ZS2.25x065",L' ',0,NULL},
{u8"CF 4ZS2.25x059",L' ',0,NULL},
{u8"CF 3.5ZS1.5x070",L' ',0,NULL},
{u8"CF 3.5ZS1.5x065",L' ',0,NULL},
{u8"CF 3.5ZS1.5x059",L' ',0,NULL},
};

PTMENU mZ_section_US_si_2_1 = { 60,0,0,16,16,8,FIXED,CMNU,CMBR,CMTX,0,0,0,0,0,(PPOLE(*)[]) &pmZ_section_US_si_2_1,NULL,NULL };

