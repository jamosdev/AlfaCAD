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

#ifdef __PRNDLG__

#define PRINTER_WINDOWS "Printer-WINDOWS"
#define PRINTER_PCX     "Printer-Image"
#define PRINTER_PDF     "Printer-PDF"
#define PRINTER9        "Printer-9"
#define PRINTER24       "Printer-24"
#define PRINTER48       "Printer-48"
#define PRINTER_ESC_P2  "Printer-ESC/P2"
#define PRINTER_LASER   "Printer-HP PCL"
#define PRINTER_DATA    "Printing"


static char* prn_config_param[] =
{
	//"Przesow Pionowy",
	//"Przesuw Pionowy HQ",
	//"Gestosc Pionowa EPSON",
	//"Gestosc Pionowa IBM",
	//"Gestosc Pionowa HQ EPSON",
	//"Gestosc Pionowa HQ IBM",
	//"Druk Draft",
	"Draft Density",
	//"Gestosc Draft IBM",
	//"Druk Normalny",
	"Better Density",
	//"Gestosc Normalna IBM",
	//"Druk Dokladny",
	"Good Density",
	//"Gestosc Dokladna IBM",
	//"Druk Specjalny",
	//"Tryb Specjalny IBM",
	"Fine Density",
	//"Gestosc Specjalna IBM",
	"Extra Fine Density",
	"Arc Section",
	//"Inicjacja Drukarki",
	//"Reset Drukarki",
  //  "Srednica Punktu",
};

static int no_prn_config_param = sizeof(prn_config_param) / sizeof(prn_config_param[0]);

static char* prn_ini_date_param[] =
{
  "Printer Type",
  "Printer Mode",
  "Printing In Scale",
  "Printing Mode",
  "Printing Rotation",
  "Printing Inversion",
  "Printing Reflection",
  "Printout On Printer",
  "Margins",
  "Very Thin Line Thickness",
  "Thin Line Thickness",
  "Thick Line Thickness",
  "Very Thick Line Thickness",
  "Extra Thick Line Thickness",
  "Top Margin",
  "Bottom Margin",
  "Left Margin",
  "Right margin",
  "Page width",
  "Page Height",
  "Printer Page width",
  "Printer Page Height",
  "Printing Scale",
  "Actual size",
  "Pause",
  "Changing Page",
  "Printing In Color",
  "Image Gray",
  "Printing In Gray",
  "Color Mode",
  "Set Page Length",
  "Printing Window",
  "Printing Sheet",
  "LPT",
  "Text display",
  "Buffering",
  "Data Compression",
  "Plotter",
  "RCF Format",
  "Fixed Name",
  "File",
  "Copies",
  "Image Saturation",
  "H Thickness Factor",
  "V Thickness Factor",
  "Roll Number",
  "WINPRINT Def",
  "Image Format",
  "Gray intensity",
  "Background"
};

static int no_prn_ini_date_param = sizeof(prn_ini_date_param) / sizeof(prn_ini_date_param[0]);

static char* prn_ini_date_param_comment[] =
{
  ";IMAGE=0, WINDOWS=1, PDF=2",
  ";not used",
  ";1-actuall scale,0-fill page",
  ";1-draft,2-better,3-good,4-fine,5-extra fine",
  ";1-rotation,0-no rotation",
  ";1-inversion, 0-no inversion",
  ";1-reflection, 0-no reflection",
  ";1-printer,0-file - depreciated",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";[mm]",
  ";scale",
  ";actual size for saving image in file",
  ";pause for page change - depreciated",
  ";",
  ";",
  ";",
  ";1-color,0-B/W",
  ";0-KCMY,1-YMCK,2-MCYK,3-GRAY - depreciated",
  ";",
  ";",
  ";",
  ";printer port",
  ";text mode",
  ";buffering in file - depreciated",
  ";data compression",
  ";plotter - depreciated",
  ";RCF Format OCE plotters - depreciated",
  ";fixed name to save image - depreciated",
  ";image file name",
  ";number of copies - depreciated",
  ";image saturation level - depreciated",
  ";horizontal line thickness correction factor",
  ";vertical line thickness correction factor",
  ";0-default, 1-roll 1, 2-roll 2 - depreciated",
  ";0-menu, 1-default",
  "; BMP, PNG, JPEG, TIFF, PCX, EPS, PDF",
  "; 3 - dark, 2 - medium, 1 - light",
  ";"
};

#define prn_comm0 u8"very thin"
#define prn_comm1 u8"thin"
#define prn_comm2 u8"thick"
#define prn_comm3 u8"very thick"
#define prn_comm4 u8"extra thick"
#define prn_comm5 u8"scale"
#define prn_comm6 u8"page"
#define prn_comm7 u8"Scale and page setup"
#define prn_comm8 u8"Printing direction"
#define prn_comm9 u8"Printing type"
//#define prn_comm10 u8"Line thickness factor H / V"
#define prn_comm10 u8"Line thick.factor H,V"
#define prn_comm11 u8"Printing type"
#define prn_comm12 u8"thickn. [mm]"
#define prn_comm13 u8"Yes"
#define prn_comm14 u8"No"
#define prn_comm15 u8""
#define prn_comm16 u8""
#define prn_comm17 u8"Draft"
#define prn_comm18 u8"Better"
#define prn_comm19 u8"Good"
#define prn_comm20 u8"Fine"
#define prn_comm21 u8"Extra fine"
#define prn_comm22 u8""
#define prn_comm23 u8"Print"
#define prn_comm24 u8"ESC"
#define prn_comm25 u8""
#define prn_comm26 u8""
#define prn_comm27 u8""
#define prn_comm28 u8""
#define prn_comm29 u8"Save"
#define prn_comm30 u8"Load"
#define prn_comm31 u8""
#define prn_comm32 u8"Preview"
#define prn_comm33 u8"Limits"

#define image_pr_tips0  u8"@Rotation"
#define image_pr_tips1  u8"Inversion"
#define image_pr_tips2	u8"Reflection"
#define image_pr_tips3	u8"Print in shades of gray"
#define image_pr_tips4	u8"Print in Black & White"
#define image_pr_tips5	u8"Print bitmaps in shades of gray"
#define image_pr_tips6	u8"Print on the printer"
#define image_pr_tips7	u8"Save in the image file"
#define image_pr_tips8	u8"Print window"
#define image_pr_tips9	u8"Print selected '@SHEET'"
#define image_pr_tips10	u8"Print in scale"
#define image_pr_tips11	u8"From page number"
#define image_pr_tips12	u8"Page width [mm]"
#define image_pr_tips13	u8"Page height [mm]"
#define image_pr_tips14	u8"Page overlaps [mm]"
#define image_pr_tips15	u8"Left margin [mm]"
#define image_pr_tips16	u8"Right margin [mm]"
#define image_pr_tips17	u8"Top margin [mm]"
#define image_pr_tips18	u8"Bottom margin [mm]"
#define image_pr_tips19	u8"Actual size"
#define image_pr_tips20	u8"Very thin"
#define image_pr_tips21	u8"Thin"
#define image_pr_tips22	u8"Thick"
#define image_pr_tips23	u8"Very thick"
#define image_pr_tips24	u8"Extra thick"
#define image_pr_tips25	u8"Save in vector PDF file"
#define image_pr_tips26 u8"Paper format"
#define image_pr_tips27 u8"Printing light background color"

#define _FILE_OPENING_ERROR_ u8"File opening error "
#define _FILE_WRITING_ERROR_ u8"File writing error "
#define _FILE_READING_ERROR_ u8"File reading error "

#define _PRINTING_ u8"Printing on printer / Saving image file"
#define _PRINTING_SERIAL_ u8"Serial printing of workshop drawings"
#define _PRINTING_SPEC_ u8"Printing of the specificaction"

#endif

#ifdef  __PLTDLG__

#define PLOTER u8"Plotter"
#define PLOTER_DATA u8"Plotting"

char* plt_config_param[] =
{
   "Plotter Type",
   "Extreme Points",
   "Resolution",
   "Centering",
   "Initiation",
   "Ending",
   "Pen Selection",
   "Pen Velocity",
   "Pen Width",
   "Pen Up",
   "Pen Down",
   "Absolute displacement",
   "Draw line",
   "Absolute Jump",
   "Coordinates Terminator",
   "Command Terminator",
   "Arc Section Length",
};

int no_plt_config_param = sizeof(plt_config_param) / sizeof(plt_config_param[0]);

static char* plt_ini_data_param[] =
{
	//"Typ Plotera",
	"Shift",
	"Rotation",
	"Scale",
	"Window",
	"Sheet",
	"Ink Plotter",
	"Port",
	"Pen Width for Fillings",
	"Fixed Name",
	"Set Page Dimensions",
	"Color Plotting",
	"255 Colors",
	"Pen Velocities",
	"Pen Widths",
	"Number of Pens",
	"Color1","Color2","Color3","Color4","Color5","Color6","Color7","Color8",
	"Color9","Color10","Color11","Color12","Color13","Color14","Color15","Color16",
	/*
	"Color17","Color18","Color19","Color20",
	"Color21","Color22","Color23","Color24","Color25","Color26","Color27","Color28","Color29","Color30",
	"Color31","Color32","Color33","Color34","Color35","Color36","Color37","Color38","Color39","Color40",
	"Color41","Color42","Color43","Color44","Color45","Color46","Color47","Color48","Color49","Color50",
	"Color51","Color52","Color53","Color54","Color55","Color56","Color57","Color58","Color59","Color60",
	"Color61","Color62","Color63","Color64","Color65","Color66","Color67","Color68","Color69","Color70",
	"Color71","Color72","Color73","Color74","Color75","Color76","Color77","Color78","Color79","Color80",
	"Color81","Color82","Color83","Color84","Color85","Color86","Color87","Color88","Color89","Color90",
	"Color91","Color92","Color93","Color94","Color95","Color96","Color97","Color98","Color99","Color100",
	"Color101","Color102","Color103","Color104","Color105","Color106","Color107","Color108","Color109","Color110",
	"Color111","Color112","Color113","Color114","Color115","Color116","Color117","Color118","Color119","Color120",
	"Color121","Color122","Color123","Color124","Color125","Color126","Color127","Color128","Color129","Color130",
	"Color131","Color132","Color133","Color134","Color135","Color136","Color137","Color138","Color139","Color140",
	"Color141","Color142","Color143","Color144","Color145","Color146","Color147","Color148","Color149","Color150",
	"Color151","Color152","Color153","Color154","Color155","Color156","Color157","Color158","Color159","Color160",
	"Color161","Color162","Color163","Color164","Color165","Color166","Color167","Color168","Color169","Color170",
	"Color171","Color172","Color173","Color174","Color175","Color176","Color177","Color178","Color179","Color180",
	"Color181","Color182","Color183","Color184","Color185","Color186","Color187","Color188","Color189","Color190",
	"Color191","Color192","Color193","Color194","Color195","Color196","Color197","Color198","Color199","Color200",
	"Color201","Color202","Color203","Color204","Color205","Color206","Color207","Color208","Color209","Color210",
	"Color211","Color212","Color213","Color214","Color215","Color216","Color217","Color218","Color219","Color220",
	"Color221","Color222","Color223","Color224","Color225","Color226","Color227","Color228","Color229","Color230",
	"Color231","Color232","Color233","Color234","Color235","Color236","Color237","Color238","Color239","Color240",
	"Color241","Color242","Color243","Color244","Color245","Color246","Color247","Color248","Color249","Color250",
	"Color251","Color252","Color253","Color254","Color255",
	"PenColor1","PenColor2","PenColor3","PenColor4","PenColor5","PenColor6","PenColor7","PenColor8",
	"PenColor9","PenColor10","PenColor11","PenColor12","PenColor13","PenColor14","PenColor15","PenColor16",
	"PenColor17","PenColor18","PenColor19","PenColor20",
	"PenColor21","PenColor22","PenColor23","PenColor24","PenColor25","PenColor26","PenColor27","PenColor28","PenColor29","PenColor30",
	"PenColor31","PenColor32","PenColor33","PenColor34","PenColor35","PenColor36","PenColor37","PenColor38","PenColor39","PenColor40",
	"PenColor41","PenColor42","PenColor43","PenColor44","PenColor45","PenColor46","PenColor47","PenColor48","PenColor49","PenColor50",
	"PenColor51","PenColor52","PenColor53","PenColor54","PenColor55","PenColor56","PenColor57","PenColor58","PenColor59","PenColor60",
	"PenColor61","PenColor62","PenColor63","PenColor64","PenColor65","PenColor66","PenColor67","PenColor68","PenColor69","PenColor70",
	"PenColor71","PenColor72","PenColor73","PenColor74","PenColor75","PenColor76","PenColor77","PenColor78","PenColor79","PenColor80",
	"PenColor81","PenColor82","PenColor83","PenColor84","PenColor85","PenColor86","PenColor87","PenColor88","PenColor89","PenColor90",
	"PenColor91","PenColor92","PenColor93","PenColor94","PenColor95","PenColor96","PenColor97","PenColor98","PenColor99","PenColor100",
	"PenColor101","PenColor102","PenColor103","PenColor104","PenColor105","PenColor106","PenColor107","PenColor108","PenColor109","PenColor110",
	"PenColor111","PenColor112","PenColor113","PenColor114","PenColor115","PenColor116","PenColor117","PenColor118","PenColor119","PenColor120",
	"PenColor121","PenColor122","PenColor123","PenColor124","PenColor125","PenColor126","PenColor127","PenColor128","PenColor129","PenColor130",
	"PenColor131","PenColor132","PenColor133","PenColor134","PenColor135","PenColor136","PenColor137","PenColor138","PenColor139","PenColor140",
	"PenColor141","PenColor142","PenColor143","PenColor144","PenColor145","PenColor146","PenColor147","PenColor148","PenColor149","PenColor150",
	"PenColor151","PenColor152","PenColor153","PenColor154","PenColor155","PenColor156","PenColor157","PenColor158","PenColor159","PenColor160",
	"PenColor161","PenColor162","PenColor163","PenColor164","PenColor165","PenColor166","PenColor167","PenColor168","PenColor169","PenColor170",
	"PenColor171","PenColor172","PenColor173","PenColor174","PenColor175","PenColor176","PenColor177","PenColor178","PenColor179","PenColor180",
	"PenColor181","PenColor182","PenColor183","PenColor184","PenColor185","PenColor186","PenColor187","PenColor188","PenColor189","PenColor190",
	"PenColor191","PenColor192","PenColor193","PenColor194","PenColor195","PenColor196","PenColor197","PenColor198","PenColor199","PenColor200",
	"PenColor201","PenColor202","PenColor203","PenColor204","PenColor205","PenColor206","PenColor207","PenColor208","PenColor209","PenColor210",
	"PenColor211","PenColor212","PenColor213","PenColor214","PenColor215","PenColor216","PenColor217","PenColor218","PenColor219","PenColor220",
	"PenColor221","PenColor222","PenColor223","PenColor224","PenColor225","PenColor226","PenColor227","PenColor228","PenColor229","PenColor230",
	"PenColor231","PenColor232","PenColor233","PenColor234","PenColor235","PenColor236","PenColor237","PenColor238","PenColor239","PenColor240",
	"PenColor241","PenColor242","PenColor243","PenColor244","PenColor245","PenColor246","PenColor247","PenColor248","PenColor249","PenColor250",
	"PenColor251","PenColor252","PenColor253","PenColor254","PenColor255",
	*/
};

static int no_plt_ini_data_param = sizeof(plt_ini_data_param) / sizeof(plt_ini_data_param[0]);

static char* plt_ini_data_param_comment[] =
{
	//";typ,MERA=2,1 inne",
	";dx, dy",
	"; 0 No,1 Yes",
	";scale",
	";0-whole drawing, 1-window",
	";0-drawing/window, 1-selected sheet",
	";0-pen plotter, 1-ink ploter",
	"",
	"",
	";fixed name of print file",
	";for HP=1, for OCe=0",
	";0=B/W, 1=color",
	";0=mapped colors, 1=255 colors RGB->CMYK",
	";2 to 25",
	";0.0 to 2.0",
	";1 to 255, default 255",
	";Pen numbers for colors and widths ,(0=SP)",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "",
	/*
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	";Wartosci kolorow Cyjan Magenta Yellow, C255 M255 Y255  zakres 0..255 ",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	*/
};

char plt_dlg_labels[][64] = {
	u8"Pen numbers    0 - skip",/* linii b.cienk/cienk/grubej/b.grubej/najgrub",*/
	u8"Speed / Thickness",
	u8"Scale, Offset",
	u8"",
	u8"Rotation, Window, Color",
	u8"Plotting to file / port",
	u8"Filling",
};

char plt_dlg_buttons[][64] = {
	u8"Plot",
	u8"ESC",
	u8"fixed name",
	u8"set page size ( HP )",
};

#define plt_dlg_labs0 u8"Legacy Plotting"
#define plt_dlg_labs1 u8"x - default"
#define plt_dlg_labs2 u8""

#define image_pl_tips0 u8"@Very thin"
#define image_pl_tips1 u8"Thin"
#define image_pl_tips2 u8"Thick"
#define image_pl_tips3 u8"Very thick"
#define image_pl_tips4 u8"Extra thick"
#define image_pl_tips5 u8"Ink plotter"
#define image_pl_tips6 u8"Rotation"
#define image_pl_tips7 u8"Plot indicated window"
#define image_pl_tips8 u8"Plot selected '@SHEET'"
#define image_pl_tips9 u8"Plotting in color"
#define image_pl_tips10 u8"Plotting in 255 colors"
#define image_pl_tips11 u8"Plotting scale"
#define image_pl_tips12 u8"Left offset [mm]"
#define image_pl_tips13 u8"Bottom offset [mm]"

#define _FILE_OPENING_ERROR_ u8"File opening error "
#define _FILE_WRITING_ERROR_ u8"File writing error "
#define _FILE_READING_ERROR_ u8"File reading error "

#define _NR_ u8"No"
#define _CM_S_ u8"[cm/s]"
#define _MM_ "[mm]"
#define _FILLINGS_ u8"fillings"

#endif

#ifdef __PCXDLG__

#define _IMAGE_FILE_IMPORT_ u8"Image file import parameters"

#define pcx_tips0 u8"@Horizontal density in dots per inch"
#define pcx_tips1 u8"Vertical density in dots per inch"
#define pcx_tips2 u8"Horizontal size in mm"
#define pcx_tips3 u8"Vertical size in mm"
#define pcx_tips4 u8"Scaled horizontal size in mm"
#define pcx_tips5 u8"Scaled vertical size in mm"
#define pcx_tips6 u8"Horizontal scale"
#define pcx_tips7 u8"Vertical scale"
#define pcx_tips8 u8"Filled background"
#define pcx_tips9 u8"Rotation angle"
#define pcx_tips10 u8"Preserve aspect ratio"
#define pcx_tips11 u8"Put on top"
#define pcx_tips12 u8"Flip horizontally"
#define pcx_tips13 u8"Flip vertically"

char header_s[] = u8"Header";
char setup_s[] = u8"Setup";
char flip_s[] = u8"Flip";

#endif

#ifdef __COLORS__

#define KOLORY "COLORS"
#define CHOOSE_COLORS u8"choose colors"

#define image_col_tips0  u8"@Select color"

#endif

#ifdef __DXFDLG__

#define _DFX_IMPORT_ u8"DXF/DWG file import parameters";
char header_dxf[] = u8"Header";
char setup_dxf[] = u8"Setup";
char setup_format[] = u8"Format";

#define images_dxf_tips0 u8"@Horizontal EXTENTS [units]"
#define images_dxf_tips1 u8"Vertical EXTENTS [units]"
#define images_dxf_tips2 u8"Horizontal LIMITS [units]"
#define images_dxf_tips3 u8"Vertical LIMITS [units]"
#define images_dxf_tips4 u8"Horizontal size [mm]"
#define images_dxf_tips5 u8"Vertical size [mm]"
#define images_dxf_tips6 u8"Left margin [mm]"
#define images_dxf_tips7 u8"Bottom margin [mm]"
#define images_dxf_tips8 u8"Units"
#define images_dxf_tips9 u8"Scale"
#define images_dxf_tips10 u8"Drawing format"
#define images_dxf_tips11 u8"Correct drawing dimensions automatically"

#endif

#ifdef __DIALOG__

#define _OTHER_ u8"֍other>>>"

#endif