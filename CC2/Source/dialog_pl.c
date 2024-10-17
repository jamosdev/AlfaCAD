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

#define PRINTER_WINDOWS "Drukarka-WINDOWS"
#define PRINTER_PCX     "Drukarka-Obraz"
#define PRINTER_PDF     "Drukarka-PDF"
#define PRINTER9        "Drukarka-9"
#define PRINTER24       "Drukarka-24"
#define PRINTER48       "Drukarka-48"
#define PRINTER_ESC_P2  "Drukarka-ESC/P2"
#define PRINTER_LASER   "Drukarka-HP PCL"
#define PRINTER_DATA    "Drukowanie"

static char* prn_config_param[] =
{
	//"Przesow Pionowy",
	//"Przesuw Pionowy HQ",
	//"Gestosc Pionowa EPSON",
	//"Gestosc Pionowa IBM",
	//"Gestosc Pionowa HQ EPSON",
	//"Gestosc Pionowa HQ IBM",
	//"Druk Draft",
	"Gestosc Uproszczona",
	//"Gestosc Draft IBM",
	//"Druk Normalny",
	"Gestosc Lepsza",
	//"Gestosc Normalna IBM",
	//"Druk Dokladny",
	"Gestosc Normalna",
	//"Gestosc Dokladna IBM",
	//"Druk Specjalny",
	//"Tryb Specjalny IBM",
	"Gestosc Dokladna",
	//"Gestosc Specjalna IBM",
	"Gestosc Specjalna",
	"Segment Luku",
	//"Inicjacja Drukarki",
	//"Reset Drukarki",
  //  "Srednica Punktu",
};

static int no_prn_config_param = sizeof(prn_config_param) / sizeof(prn_config_param[0]);

static char* prn_ini_date_param[] =
{
  "Typ Drukarki",
  "Tryb Drukarki",
  "Wydruk W Skali",
  "Rodzaj Wydruku",
  "Obrot Rysunku",
  "Odwrocenie Rysunku",
  "Lustrzane odbicie",
  "Wydruk Na Drukarke",
  "Margines",
  "Szerokosc Linii Bardzo Cienkiej",
  "Szerokosc Linii Cienkiej",
  "Szerokosc Linii Grubej",
  "Szerokosc Linii Bardzo Grubej",
  "Szerokosc Linii Najgrubszej",
  "Gorny margines",
  "Dolny margines",
  "Lewy margines",
  "Prawy margines",
  "Szerokosc wydruku",
  "Wysokosc wydruku",
  "Szerokosc wydruku drukarki",
  "Wysokosc wydruku drukarki",
  "Skala",
  "Rzeczywiste wymiary",
  "Pauza",
  "Zmiana strony",
  "Wydruk w kolorze",
  "Obraz szary",
  "Szary",
  "Tryb koloru",
  "Ustaw dlugosc strony",
  "Drukuj okno",
  "Drukuj arkusz",
  "LPT",
  "Text display",
  "Buforowanie",
  "Kompresja danych",
  "Ploter",
  "RCF Format",
  "Stala nazwa",
  "Plik",
  "Liczba kopii",
  "Nasycenie obrazu",
  "Korekta grubosci H",
  "Korekta grubosci V",
  "Numer rolki",
  "WINPRINT Def",
  "Format pliku obrazu",
  "Intensywnosc szarosci",
  "Wydruk tla"
};

static int no_prn_ini_date_param = sizeof(prn_ini_date_param) / sizeof(prn_ini_date_param[0]);

static char* prn_ini_date_param_comment[] =
{
  ";OBRAZ=0, WINDOWS=1, PDF=2",
  ";nie uzywane",
  ";1-w skali,0-wypelnienie strony",
  ";1-uproszczony,2-lepszy,3-normalny,4-dokladny,5-specjalny",
  ";1-obrot,0-bez obrotu",
  ";1-odwrocenie, 0-normalnie",
  ";1-lustro, 0-normalnie",
  ";1-na drukarke,0-do zbioru - nie uzywane",
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
  ";skala wydruku",
  ";rzeczywiste wymiary dla zapisu do pliku",
  ";pauza na zmiane arkusza,0-NIE,1-TAK",
  ";",
  ";",
  ";",
  ";0-kolor,1-GRAY",
  ";0-KCMY,1-YMCK,2-MCYK,3-GRAY",
  ";",
  ";",
  ";",
  ";numer portu drukarki",
  ";przelaczenie ekranu w tryb tekstowy",
  ";buforowanie wydruku na dysku (siec)",
  ";kompresja danych",
  ";ploter",
  ";RCF Format dla ploterow OCE",
  ";stała nazwa zbioru wydrukow",
  ";nazwa pliku wydruku (stala nazwa)",
  ";liczba kopii wydruku",
  ";stopien nasycenia obrazu",
  ";korekta grubosci linii poziomej",
  ";korekta grubosci linii pionowej",
  ";0-default, 1-rolka 1, 2-rolka 2",
  ";0-menu, 1-default",
  ";BMP, PNG, JPEG, TIFF, PCX, EPS, PDF",
  ";3 - ciemny, 2 - umiarkowany, 1 - jasny",
  ";",
};

#define prn_comm0 u8"bardzo cienka"
#define prn_comm1 u8"cienka"
#define prn_comm2 u8"gruba"
#define prn_comm3 u8"bardzo gruba"
#define prn_comm4 u8"najgrubsza"
#define prn_comm5 u8"skala"
#define prn_comm6 u8"strona"
#define prn_comm7 u8"Skala i ustawienie strony"
#define prn_comm8 u8"Kierunek wydruku"
#define prn_comm9 u8"Rodzaj wydruku"
#define prn_comm10 u8"Wsp.grubości linii H  /  V"
#define prn_comm11 u8"Rodzaj wydruku:"
#define prn_comm12 u8"Grub. [mm]"
#define prn_comm13 u8"Tak"
#define prn_comm14 u8"Nie"
#define prn_comm15 u8""
#define prn_comm16 u8""
#define prn_comm17 u8"Uproszczony"
#define prn_comm18 u8"Lepszy"
#define prn_comm19 u8"Normalny"
#define prn_comm20 u8"Dokładny"
#define prn_comm21 u8"Specjalny"
#define prn_comm22 u8""
#define prn_comm23 u8"Drukuj"
#define prn_comm24 u8"ESC"
#define prn_comm25 u8""
#define prn_comm26 u8""
#define prn_comm27 u8""
#define prn_comm28 u8""
#define prn_comm29 u8"Zapis"
#define prn_comm30 u8"Odczyt"
#define prn_comm31 u8""
#define prn_comm32 u8"Podgląd"
#define prn_comm33 u8"Granice"

#define image_pr_tips0  u8"@Obrót"
#define image_pr_tips1	u8"Odwrócenie"
#define image_pr_tips2	u8"Lustrzane odbicie"
#define image_pr_tips3	u8"Drukuj w odcieniach szarości"
#define image_pr_tips4	u8"Drukuj w trybie czarno-białym"
#define image_pr_tips5	u8"Drukuj bitmapy w odcieniach szarości"
#define image_pr_tips6	u8"Wydruk na drukarce"
#define image_pr_tips7	u8"Zapis w pliku graficznego"
#define image_pr_tips8	u8"Drukuj wskazane okno"
#define image_pr_tips9	u8"Drukuj wybrany arkusz '@SHEET'"
#define image_pr_tips10	u8"Drukuj w zadanej skali"
#define image_pr_tips11	u8"Drukuj od strony numer:"
#define image_pr_tips12	u8"Szerokość strony [mm]"
#define image_pr_tips13	u8"Wysokość strony [mm]"
#define image_pr_tips14	u8"Zakładki stron [mm]"
#define image_pr_tips15	u8"Lewy margines [mm]"
#define image_pr_tips16	u8"Prawy margines [mm]"
#define image_pr_tips17	u8"Górny margines"
#define image_pr_tips18	u8"Dolny margines"
#define image_pr_tips19	u8"Rzeczywiste wymiary rysunku"
#define image_pr_tips20	u8"Bardzo cienka"
#define image_pr_tips21	u8"Cienka"
#define image_pr_tips22	u8"Gruba"
#define image_pr_tips23	u8"Bardzo gruba"
#define image_pr_tips24	u8"Najgrubsza"
#define image_pr_tips25	u8"Zapis w wektorowym pliku PDF"
#define image_pr_tips26 u8"Format arkusza"
#define image_pr_tips27 u8"Wydruk koloru jasnego tła"

#define _FILE_OPENING_ERROR_ u8"Błąd otwarcia pliku "
#define _FILE_WRITING_ERROR_ u8"Błąd zapisu pliku "
#define _FILE_READING_ERROR_ u8"Błąd odczytu pliku "

#define _PRINTING_ u8"Wydruk rysunku na drukarce / zapis pliku"
#define _PRINTING_SERIAL_ u8"Wydruk seryjny rysunków warsztatowych"
#define _PRINTING_SPEC_ u8"Wydruk specyfikacji pustaków"

#endif

#ifdef  __PLTDLG__

#define PLOTER u8"Ploter"
#define PLOTER_DATA u8"Plotowanie"

char* plt_config_param[] =
{
   "Typ Plotera",
   "Punkty Skrajne",
   "Rozdzielczosc",
   "Centrowanie",
   "Wzorzec Inicjacji",
   "Wzorzec Zakonczenia",
   "Selekcja Pisaka",
   "Predkosc Pisaka",
   "Grubosc Pisaka",
   "Podniesienie Pisaka",
   "Opuszczenie Pisaka",
   "Przemieszczenie Bezwzgledne",
   "Rysuj Linie",
   "Skok Bezwzgledny",
   "Terminator Wspolrzednych",
   "Terminator Komend",
   "Segment Luku",
};

int no_plt_config_param = sizeof(plt_config_param) / sizeof(plt_config_param[0]);

static char* plt_ini_data_param[] =
{
	//"Typ Plotera",
	"Przesuniecie",
	"Rotacja",
	"Skala",
	"Drukuj okno",
	"Drukuj arkusz",
	"Ploter atramentowy",
	"Port",
	"Grubosc Pisaka Do Wypelnien",
	"Stala nazwa",
	"Ustaw wymiary arkusza",
	"Wydruk w kolorze",
	"255 kolorow",
	"Predkosci pisakow",
	"Grubosci linii",
	"Liczba pisakow",
	"Kolor1","Kolor2","Kolor3","Kolor4","Kolor5","Kolor6","Kolor7","Kolor8",
	"Kolor9","Kolor10","Kolor11","Kolor12","Kolor13","Kolor14","Kolor15","Kolor16",
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
	";obrot 0 NIE,1 TAK",
	";skala",
	";0-caly rysunek, 1-okno",
	";0-rysunek/okno, 1-wybrany arkusz",
	";0-ploter pisakowy, 1-ploter atramentowy",
	"",
	"",
	";stala nazwa zbioru wydrukow",
	";dla ploterow HP=1, dla ploterow OCe=0",
	";0=mono, 1=kolor",
	";0=kolory mapowane, 1=255 kolorow RGB->CMYK",
	";2 do 25",
	";0.0 do 2.0",
	";1 do 255, domyslnie 255",
	";Numery pisakow dla kolorow i grubosci ,(0=SP)",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	/*"", "", "",
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
	u8"Numery pisaków    0 - pomiń",/* linii b.cienk/cienk/grubej/b.grubej/najgrub",*/
	u8"Prędkość / Grubość",
	u8"Skala, Przesunięcie",
	u8"",
	u8"Obrót, Okno, Kolor",
	u8"Wydruk do zbioru / portu",
	u8"Wypełnienia",
};

char plt_dlg_buttons[][64] = {
	u8"Plotuj",
	u8"ESC",
	u8"stała nazwa",
	u8"ustaw wymiary arkusza ( HP )",
};

#define plt_dlg_labs0 u8"Wydruk na ploter"
#define plt_dlg_labs1 u8"x - domyślna"
#define plt_dlg_labs2 u8""

#define image_pl_tips0 u8"@Bardzo cienka"
#define image_pl_tips1 u8"Cienka"
#define image_pl_tips2 u8"Gruba"
#define image_pl_tips3 u8"Bardzo gruba"
#define image_pl_tips4 u8"Najgrubsza"
#define image_pl_tips5 u8"Ploter atramentowy"
#define image_pl_tips6 u8"Obrót"
#define image_pl_tips7 u8"Plotowanie okna"
#define image_pl_tips8 u8"Plotowanie wybranego arkusza '@SHEET'"
#define image_pl_tips9 u8"Plotowanie w kolorze"
#define image_pl_tips10 u8"Plotowanie w 255 kolorach"
#define image_pl_tips11 u8"Skala"
#define image_pl_tips12 u8"Przesunięcie w poziomie [mm]"
#define image_pl_tips13 u8"Przesunięcie w pionie [mm]"

#define _FILE_OPENING_ERROR_ u8"Błąd otwarcia pliku "
#define _FILE_WRITING_ERROR_ u8"Błąd zapisu pliku "
#define _FILE_READING_ERROR_ u8"Błąd odczytu pliku "

#define _NR_ u8"Nr"
#define _CM_S_ u8"[cm/s]"
#define _MM_ "[mm]"
#define _FILLINGS_ u8"wypełnienia"

#endif

#ifdef __PCXDLG__

#define _IMAGE_FILE_IMPORT_ u8"Parametery importu pliku graficznego";

#define pcx_tips0 u8"@Pozioma gęstość w pxl na cal"
#define pcx_tips1 u8"Pionowa gęstość w pxl na cal"
#define pcx_tips2 u8"Pozioma wielkość w mm"
#define pcx_tips3 u8"Pionowa wielkość w mm"
#define pcx_tips4 u8"Skalowana pozioma wielkość w mm"
#define pcx_tips5 u8"Skalowana pionowa wielkość w mm"
#define pcx_tips6 u8"Pozioma skala"
#define pcx_tips7 u8"Pionowa skala"
#define pcx_tips8 u8"Wypełnienie tła"
#define pcx_tips9 u8"Kąt obrotu"
#define pcx_tips10 u8"Zachowaj proporcje"
#define pcx_tips11 u8"Połóż na wierzchu"
#define pcx_tips12 u8"Odwróź poziomo"
#define pcx_tips13 u8"Odwróć pionowo"

char header_s[] = u8"Nagłówek";
char setup_s[] = u8"Parametry";
char flip_s[] = u8"Odwrócenie";

#endif

#ifdef __COLORS__

#define KOLORY "KOLORY"
#define CHOOSE_COLORS u8"wybierz kolor"

#define image_col_tips0  u8"@Wybierz kolor"

#endif

#ifdef __DXFDLG__

#define _DFX_IMPORT_ u8"Parametery importu pliku DXF/DWG";

char header_dxf[] = u8"Nagłówek";
char setup_dxf[] = u8"Parametry";
char setup_format[] = u8"Format";

#define images_dxf_tips0 u8"@Poziome EXTENTS [jednostki]"
#define images_dxf_tips1 u8"Pionowe EXTENTS [jednostki]"
#define images_dxf_tips2 u8"Poziome LIMITS [jednostki]"
#define images_dxf_tips3 u8"Pionowe LIMITS [jednostki]"
#define images_dxf_tips4 u8"Szerokosc rysunku [mm]"
#define images_dxf_tips5 u8"Wysokosc rysunku [mm]"
#define images_dxf_tips6 u8"Lewy margines [mm]"
#define images_dxf_tips7 u8"Dolny margines [mm]"
#define images_dxf_tips8 u8"Jednpostki"
#define images_dxf_tips9 u8"Skala"
#define images_dxf_tips10 u8"Format arkusza"
#define images_dxf_tips11 u8"Skoryguj automatycznie wymiary arkusza"

#endif

#ifdef __DIALOG__

#define _OTHER_ u8"֍inny>>> "

#endif
