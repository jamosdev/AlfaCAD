#include "IH_section_UK_si_standards.c"

POLE pmIH_section_UK_si[] = {
{u8"BS 4-1:1993",L' ',0,&mIH_section_UK_si_0},
{u8"BS 4-1:2005",L' ',0,&mIH_section_UK_si_1},
{u8"BS EN 10365:2017",L' ',0,&mIH_section_UK_si_2},
{u8"DIN EN 16828:2015-04; BS 4-1:2005",L' ',0,&mIH_section_UK_si_3},
};

TMENU mIH_section_UK_si = { 4,0,0,34,16,8,0,CMNU,CMBR,CMTX,0,0,0,0,0,(POLE(*)[]) &pmIH_section_UK_si,NULL,NULL };

