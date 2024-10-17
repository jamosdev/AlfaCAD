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

#ifdef __RYSUJ__

extern TMENU mSteelUS;
extern TMENU mSteelEU;
extern TMENU mSteelUK;
extern TMENU mTimberUS;
extern TMENU mWoodSpeciesUS;

POLE pmZmienTeksty[] = {
	{u8"Szukaj tekstu\0",'S',3,NULL},
	{u8"Zmień teksty",'Z',90, NULL},
	{u8"Automatyczna numeracja", 'A', 91, NULL},
	//	{u8"Przesunięcie numeracji", 'P', 0,NULL},
};

TMENU mZmienTeksty = { 3, 0, 0, 22, 15, 9, ICONS, CMNU, CMBR, CMTX, 0, 15, 0, 0,0,(POLE(*)[]) & pmZmienTeksty, NULL, NULL };

POLE pmChangeProperties[] = {
	{u8"Zmień",'Z',43, NULL},
	{u8"popraw krzywe Béziera", 'B',648, NULL},
    {u8"Wektory", 'W',770, NULL},
};

TMENU mChangeProperties = { 3, 0, 0, 22, 15, 9, ICONS, CMNU, CMBR, CMTX, 0, 18, 0, 0,0,(POLE(*)[]) & pmChangeProperties, NULL, NULL };

POLE pmWoodMoistureUS[] = {
        {u8"Green",L' ',0,&mWoodSpeciesUS},
        {u8"12%",L' ',0,&mWoodSpeciesUS}};

TMENU mWoodMoistureUS = { 2,0,0,6,16,8,0,CMNU,CMBR,CMTX,0,0,0,0,0,(POLE(*)[]) &pmWoodMoistureUS,NULL,NULL };

POLE pmMaterialUS[] = {
        {u8"Stal",'S',775, NULL}, //&mSteelUS
        {u8"Drewno", 'D',785, &mWoodMoistureUS}, //&mTimberUS
};

TMENU mMaterialUS = { 2, 0, 0, 12, 15, 9, ICONS, CMNU, CMBR, CMTX, 0, 3, 0, 0,0,(POLE(*)[])&pmMaterialUS, NULL, NULL };

POLE pmRegion[] = {
        {u8"US",'U',772, &mMaterialUS},
        {u8"EU", 'E',773, NULL}, //&mSteelEU
        {u8"UK", 'B',774, NULL}, //&mSteelUK
};

TMENU mRegion = { 3, 0, 0, 8, 15, 9, ICONS, CMNU, CMBR, CMTX, 0, 1, 0, 0,0,(POLE(*)[])&pmRegion, NULL, NULL };


POLE pmApplications[] = {
        {u8"Statyka i dynamika",L'S',733, NULL},
        {u8"Animuj dynamikę",L'A',817, NULL},
        {u8"Wybór przekrojów elementów",L'W',775, &mRegion},
};

TMENU mApplications = { 3, 0, 0, 22, 15, 9, ICONS, CMNU, CMBR, CMTX, 0, 21, 0, 0,0,(POLE(*)[])&pmApplications, NULL, NULL };


POLE pmenug[] = {
	{u8"Rysuj\0",'R',57,NULL},
	{u8"Blok\0",'B',1,NULL},
	{u8"Edycja\0",'E',2,NULL},
	{u8"Zmień właściwości\0\0",'Z',43,&mChangeProperties},
	{u8"szukaj / zmień Teksty\0",'T',4,&mZmienTeksty},
	{u8"Wymiarowanie\0",'W',5,NULL},
	{u8"kreSkowanie\0",'S',6,NULL},
	{u8"Geometria\0",'G',7,NULL},
	{u8"Makro\0",'M',8,NULL},
	{u8"Parametry\0",'P',9,NULL},
	{u8"Opcje\0",'O',10,NULL},
    {u8"Aplikacje\0",'A',753,&mApplications},
	{u8"Dysk\0",'D',81,NULL},
	{u8"Koniec pracy\0",'K',12,NULL},
	{u8"zamknij okno\0",'X',598,NULL},
};

#define _BITMAPS_ u8"Bitmaps"
#define _PLUGINS_ u8"plugins"
#define _PLUGIN_BITMAPS_ u8"plugins/bitmaps"

#endif