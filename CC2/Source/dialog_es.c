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

#define PRINTER_WINDOWS u8"Impresora-WINDOWS"
#define PRINTER_PCX     u8"Impresora-Image"
#define PRINTER_PDF     u8"Impresora-PDF"
#define PRINTER9        u8"Impresora-9"
#define PRINTER24       u8"Impresora-24"
#define PRINTER48       u8"Impresora-48"
#define PRINTER_ESC_P2  u8"Impresora-ESC/P2"
#define PRINTER_LASER   u8"Impresora-HP PCL"
#define PRINTER_DATA    u8"Impresión"


static char* prn_config_param[] =
{
	//"Przesow Pionowy",
	//"Przesuw Pionowy HQ",
	//"Gestosc Pionowa EPSON",
	//"Gestosc Pionowa IBM",
	//"Gestosc Pionowa HQ EPSON",
	//"Gestosc Pionowa HQ IBM",
	//"Druk Draft",
	u8"Calado Densidad",
	//"Gestosc Draft IBM",
	//"Druk Normalny",
	u8"Mejor Densidad",
	//"Gestosc Normalna IBM",
	//"Druk Dokladny",
	u8"Buena Densidad",
	//"Gestosc Dokladna IBM",
	//"Druk Specjalny",
	//"Tryb Specjalny IBM",
	u8"Fina Densidad",
	//"Gestosc Specjalna IBM",
	u8"Extra Fina Densidad",
	u8"Sección de Arco",
	//"Inicjacja Drukarki",
	//"Reset Drukarki",
  //  "Srednica Punktu",
};

static int no_prn_config_param = sizeof(prn_config_param) / sizeof(prn_config_param[0]);

static char* prn_ini_date_param[] =
{
  u8"Tipo de Impresora",
  u8"Modo de Impresora",
  u8"Impresión en Escala",
  u8"Modo de Impresión",
  u8"Rotación de Impresión",
  u8"Inversión de Impresión",
  u8"Reflejo de Impresión",
  u8"Impresión en Impresora",
  u8"Márgenes",
  u8"Grosor de Línea Muy Delgada",
  u8"Grosor de Línea Fina",
  u8"Grosor de Línea Gruesa",
  u8"Grosor de Línea Muy Gruesa",
  u8"Grosor de Línea Extra Gruesa",
  u8"Margen Superior",
  u8"Margen Inferior",
  u8"Margen Izquierdo",
  u8"Margen Derecho",
  u8"Ancho de Página",
  u8"Altura de Página",
  u8"Ancho de la Página Impresora",
  u8"Altura de la Página Impresora",
  u8"Escala de Impresión",
  u8"Tamaño Real",
  u8"Pausa",
  u8"Cambio de Página",
  u8"Impresión en Color",
  u8"Imagen Gris",
  u8"Impresión en Gris",
  u8"Modo de Color",
  u8"Establecer Longitud de Página",
  u8"Imprimir Ventana",
  u8"Imprimir Hoja",
  u8"LPT",
  u8"Visualización de Texto",
  u8"Almacenamiento en Búfer",
  u8"Compresión de Datos",
  u8"Trazador",
  u8"Formato RCF",
  u8"Nombre Fijo",
  u8"Archivo",
  u8"Copias",
  u8"Saturación de Imagen",
  u8"Factor de Espesor H",
  u8"Factor de Espesor V",
  u8"Número de rollo",
  u8"WINPRINT Def",
  u8"Formato de Imagen",
  u8"Intensidad de Gris",
  u8"Fondo"
};

static int no_prn_ini_date_param = sizeof(prn_ini_date_param) / sizeof(prn_ini_date_param[0]);

static char* prn_ini_date_param_comment[] =
{
  u8";IMAGE=0, WINDOWS=1, PDF=2",
  u8";no utilizado",
  u8";1-escala real, página de relleno 0",
  u8";1 borrador, 2 mejor, 3 buena, 4 muy buena, 5 especial",
  u8";1-rotación, 0-sin rotación",
  u8";1-inversión, 0-sin inversión",
  u8";1-reflexión, 0-sin reflexión",
  u8";1 impresora, 0 archivos - en desuso",
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
  ";tamaño real para guardar la imagen en el archivo",
  ";pausa por cambio de página - depreciado",
  ";",
  ";",
  ";",
  ";1-color,0-B/W",
  ";0-KCMY,1-YMCK,2-MCYK,3-GRAY - depreciado",
  ";",
  ";",
  ";",
  ";puerto de impresora",
  ";modo de texto",
  ";almacenamiento en búfer en el archivo - depreciado",
  ";compresión de datos",
  ";depreciado",
  ";Trazadores OCE formato RCF - depreciados",
  ";nombre fijo para guardar imagen - depreciado",
  ";nombre de archivo de imagen",
  ";número de copias - depreciado",
  ";nivel de saturación de imagen - depreciado",
  ";factor de corrección del grosor de la línea horizontal",
  ";factor de corrección del grosor de la línea vertical",
  "0-predeterminado, 1-rollo 1, 2-rollo 2 - depreciado",
  ";0-menú, 1-predeterminado",
  ";BMP, PNG, JPEG, TIFF, PCX, EPS, PDF",
  ";3 - oscuro, 2 - medio, 1 - claro",
  ";"
};

#define prn_comm0 u8"muy delgada"
#define prn_comm1 u8"fina"
#define prn_comm2 u8"gruesa"
#define prn_comm3 u8"muy gruesa"
#define prn_comm4 u8"extra gruesa"
#define prn_comm5 u8"escala"
#define prn_comm6 u8"página"
#define prn_comm7 u8"Configuración de página y escala"
#define prn_comm8 u8"Dirección de impresión"
#define prn_comm9 u8"Tipo de impresión"
//#define prn_comm10 u8"Line thickness factor H / V"
#define prn_comm10 u8"Factor de espesor de línea H / V"
#define prn_comm11 u8"Tipo de impresión"
#define prn_comm12 u8"grosor [mm]"
#define prn_comm13 u8"Sí"
#define prn_comm14 u8"No"
#define prn_comm15 u8""
#define prn_comm16 u8""
#define prn_comm17 u8"Borrador"
#define prn_comm18 u8"Mejor"
#define prn_comm19 u8"Buena"
#define prn_comm20 u8"Muy buena"  
#define prn_comm21 u8"Especial"
#define prn_comm22 u8""
#define prn_comm23 u8"Imprimir"
#define prn_comm24 u8"ESC"
#define prn_comm25 u8""
#define prn_comm26 u8""
#define prn_comm27 u8""
#define prn_comm28 u8""
#define prn_comm29 u8"Guardar"
#define prn_comm30 u8"Cargue"
#define prn_comm31 u8""
#define prn_comm32 u8"Vista previa"
#define prn_comm33 u8"Límites"

#define image_pr_tips0  u8"@Rotación"
#define image_pr_tips1  u8"Inversión"
#define image_pr_tips2	u8"Reflexión"
#define image_pr_tips3	u8"Impresión en tonos de gris"
#define image_pr_tips4	u8"Impresión en blanco y negro"
#define image_pr_tips5	u8"Impresión de mapas de bits en tonos de gris"
#define image_pr_tips6	u8"Imprimir en la impresora"
#define image_pr_tips7	u8"Guardar en el archivo de imagen"
#define image_pr_tips8	u8"Imprimir ventana"
#define image_pr_tips9	u8"Imprimir '@SHEET' seleccionado"
#define image_pr_tips10	u8"Imprimir en escala"
#define image_pr_tips11	u8"Desde el número de página"
#define image_pr_tips12	u8"Ancho de página [mm]"
#define image_pr_tips13	u8"Altura de página [mm]"
#define image_pr_tips14	u8"Superposición de páginas [mm]"
#define image_pr_tips15	u8"Margen izquierdo [mm]"
#define image_pr_tips16	u8"Margen derecho [mm]"
#define image_pr_tips17	u8"Margen superior [mm]"
#define image_pr_tips18	u8"Margen inferior [mm]"
#define image_pr_tips19	u8"Tamaño real"
#define image_pr_tips20	u8"Muy delgada"
#define image_pr_tips21	u8"Fina"
#define image_pr_tips22	u8"Gruesa"
#define image_pr_tips23	u8"Muy gruesa"
#define image_pr_tips24	u8"Extra gruesa"
#define image_pr_tips25	u8"Guardar en archivo PDF vectorial"
#define image_pr_tips26 u8"formato papel"
#define image_pr_tips27 u8"Impresión de color de fondo claro"

#define _FILE_OPENING_ERROR_ u8"Error al abrir el archivo "
#define _FILE_WRITING_ERROR_ u8"Error de escritura de archivo "
#define _FILE_READING_ERROR_ u8"Error de lectura de archivo "

#define _PRINTING_ u8"Imprimir en impresora / Guardar archivo de imagen"
#define _PRINTING_SERIAL_ u8"Impresión en serie de planos de taller"
#define _PRINTING_SPEC_ u8"Impresión de la especificación"

#endif

#ifdef  __PLTDLG__

#define PLOTER u8"Trazador"
#define PLOTER_DATA u8"Trazando"

char* plt_config_param[] =
{
   u8"Tipo de Trazador",
   u8"Puntos Extremos",
   u8"Resolución",
   u8"Centrado",
   u8"Iniciación",
   u8"Finalización",
   u8"Selección de Pluma",
   u8"Velocidad de Pluma",
   u8"Ancho de Pluma",
   u8"Pluma Arriba",
   u8"Pluma Abajo",
   u8"Desplazamiento Absoluto",
   u8"Dibujar Línea",
   u8"Salto Absoluto",
   u8"Terminador de Coordenadas",
   u8"Terminador de Comando",
   u8"Longitud de la Sección del Arco",
};

int no_plt_config_param = sizeof(plt_config_param) / sizeof(plt_config_param[0]);

static char* plt_ini_data_param[] =
{
	//"Typ Plotera",
	u8"Cambio",
	u8"Rotación",
	u8"Escala",
	u8"Ventana",
	u8"Sábana",
	u8"Trazador de tinta",
	u8"Puerto",
	u8"Ancho de pluma para rellenos",
	u8"Nombre fijo",
	u8"Establecer dimensiones de página",
	u8"Trazado de color",
	u8"255 colores",
	u8"Velocidades de plumas",
	u8"Anchos de plumas",
	u8"Número de plumas",
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
	"; 0 No,1 Sí",
	";escala",
	";0-dibujo completo, 1-ventana",
	";0-dibujo/ventana, 1-hoja seleccionada",
	";0-trazador de pluma, 1-trazador de tinta",
	"",
	"",
	";nombre fijo del archivo de impresión",
	";para HP=1, para OCE=0",
	";0=B/W, 1=color",
	";colores mapeados, 1=255 colores RGB->CMYK",
	";2 a 25",
	";0.0 a 2.0",
	";1 a 255, predeterminado 255",
	";Números de pluma para colores y anchos, (0=SP)",
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
	u8"Pluma números   0 - saltar",/* linii b.cienk/cienk/grubej/b.grubej/najgrub",*/
	u8"Velocidad / Espesor",
	u8"Escala, desplazamiento",
	u8"",
	u8"Rotación, Ventana, Color",
	u8"Trazado en archivo / puerto",
	u8"Relleno",
};

char plt_dlg_buttons[][64] = {
	u8"Trazando",
	u8"ESC",
	u8"Nombre fijo",
	u8"establecer tamaño de página ( HP )",
};

#define plt_dlg_labs0 u8"Trazado heredado"
#define plt_dlg_labs1 u8"x - predeterminado"
#define plt_dlg_labs2 u8""

#define image_pl_tips0 u8"@Muy delgada"
#define image_pl_tips1 u8"Fina"
#define image_pl_tips2 u8"Gruesa"
#define image_pl_tips3 u8"Muy gruesa"
#define image_pl_tips4 u8"Extra gruesa"
#define image_pl_tips5 u8"Trazador de tinta"
#define image_pl_tips6 u8"Rotación"
#define image_pl_tips7 u8"Trazar ventana indicada"
#define image_pl_tips8 u8"Trazar '@SHEET' seleccionado"
#define image_pl_tips9 u8"Trazado en color"
#define image_pl_tips10 u8"Trazado en 255 colores"
#define image_pl_tips11 u8"Escala de trazado"
#define image_pl_tips12 u8"Desplazamiento a la izquierda [mm]"
#define image_pl_tips13 u8"Desplazamiento a la inferior [mm]"

#define _FILE_OPENING_ERROR_ u8"Error al abrir el archivo "
#define _FILE_WRITING_ERROR_ u8"Error de escritura de archivo "
#define _FILE_READING_ERROR_ u8"Error de lectura de archivo "

#define _NR_ u8"No"
#define _CM_S_ u8"[cm/s]"
#define _MM_ "[mm]"
#define _FILLINGS_ u8"rellenos"

#endif

#ifdef __PCXDLG__

#define _IMAGE_FILE_IMPORT_ u8"Parámetros de importación de archivos de imagen"

#define pcx_tips0 u8"@Densidad horizontal en puntos por pulgada"
#define pcx_tips1 u8"Densidad vertical en puntos por pulgada"
#define pcx_tips2 u8"Tamaño horizontal en mm"
#define pcx_tips3 u8"Tamaño vertical en mm"
#define pcx_tips4 u8"Tamaño horizontal escalado en mm"
#define pcx_tips5 u8"Tamaño vertical escalado en mm"
#define pcx_tips6 u8"Escala horizontal"
#define pcx_tips7 u8"Escala vertical"
#define pcx_tips8 u8"Relleno del fondo"
#define pcx_tips9 u8"Ángulo de rotación"
#define pcx_tips10 u8"Preservar la relación de aspecto"
#define pcx_tips11 u8"Poner encima"
#define pcx_tips12 u8"Voltear horizontalmente"
#define pcx_tips13 u8"Voltear verticalmente"

char header_s[] = u8"Encabezado";
char setup_s[] = u8"Configuración";
char flip_s[] = u8"Voltear";

#endif

#ifdef __COLORS__

#define KOLORY u8"COLORES"
#define CHOOSE_COLORS u8"elegir colores"

#define image_col_tips0  u8"@Seleccionar el color"

#endif

#ifdef __DXFDLG__

#define _DFX_IMPORT_ u8"Parámetros de importación de archivos DXF/DWG";
char header_dxf[] = u8"Encabezado";
char setup_dxf[] = u8"Configuración";
char setup_format[] = u8"Formato";

#define images_dxf_tips0 u8"@EXTENTS Horizontales [unidades]"
#define images_dxf_tips1 u8"EXTENTS Verticales [unidades]"
#define images_dxf_tips2 u8"LIMITS Horizontales [unidades]"
#define images_dxf_tips3 u8"LIMITS Verticales [unidades]"
#define images_dxf_tips4 u8"Tamaño horizontal [mm]"
#define images_dxf_tips5 u8"Vertical size [mm]"
#define images_dxf_tips6 u8"Tamaño vertical [mm]"
#define images_dxf_tips7 u8"Margen inferior [mm]"
#define images_dxf_tips8 u8"Unidades"
#define images_dxf_tips9 u8"Escala"
#define images_dxf_tips10 u8"Formato de dibujo"
#define images_dxf_tips11 u8"Corregir las dimensiones del dibujo automáticamente"

#endif

#ifdef __DIALOG__

#define _OTHER_ u8"֍otro >>>"

#endif