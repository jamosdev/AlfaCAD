#define MAXWZLEN  32         /*maksymalna dlugosc wzorca*/
#define MAXNPEN   255        /*liczba pisakow - dla plotera pisakowego*/
#define MaxNColor 255        /*liczba kolorow*/
#define MaxPColor 255        /*liczba kolorow pisakow dla plotera atramentowego*/


typedef struct
{
	int type;      /*1, 2, 99*/
    long xmin, ymin, xmax, ymax;        /*punkty skrajne*/
    int rozdz;				/*rozdzielczosc (kroki / mm)*/
    int origin;                        /*centrowanie 0 1 */
    char ini [MAXWZLEN];		/*wzorzec inicjacji*/
    char end [MAXWZLEN];		/*wzorzec "zamkniecia" plotera*/
    char pen_sel [MAXWZLEN];		/*wzorzec selekcji pisaka*/
    char pen_speed [MAXWZLEN];		/*predkosc pisaka*/
    char pen_width_ink [MAXWZLEN];      /*grubosc pisaka*/
    char pen_up [MAXWZLEN];		/*podniesienie pisaka*/
    char pen_dn [MAXWZLEN];
    char pen_abs [MAXWZLEN];		/*przesuniecie pisaka do wspolrzednych absolutnych*/
    char pen_line [MAXWZLEN];	  	/*Rysuj linie (dla MERA POLTIC)*/
    char pen_move [MAXWZLEN];	  	/*Przesun pisak bez rysowania (dla MERA POLTIC)*/
    char ter_wsp [MAXWZLEN];
    char ter_kom [MAXWZLEN];
    double  l_luk;	/*dlugosc odcinka prostego luku w milimetrach*/
    double  dx0;              /* przesuniecie przy centrowaniu*/
    double  dy0;

} T_Plt_Config, *T_PTR_Plt_Config ;

typedef struct
{
    int line_bc;       /*numer pisaka linii bardzo cienkiej*/
    int line_c;        /*numer pisaka linii cienkiej*/
    int line_g;        /*numer pisaka linii grubej*/
    int line_bg;       /*numer pisaka linii bardzo grubej*/
    int line_ng;       /*numer pisaka linii najgrubszej*/
}
T_Pen_Line ;

typedef struct
{
    int c;        /*nasycenie koloru cyjan*/
    int m;        /*nasycenie koloru magenta*/
    int y;        /*nasycenie koloru yellow*/
    int c255;        /*nasycenie koloru cyjan*/
    int m255;        /*nasycenie koloru magenta*/
    int y255;        /*nasycenie koloru yellow*/
}
T_Pen_Color ;

typedef struct		/*dane ustawiane przed plotowaniem */
{
    long dx, dy;	/*przesuniecie lewego dolnego rogu rysunku*/
			/*w stosunku do lewego dolnego rogu plotera*/
    double xp, yp, xk, yk; /* okno do plotowania*/
    double xp_w, yp_w, xk_w, yk_w; /* wewnetrzne okno do plotowania*/
    BOOL rotation;       /*obrot rysunku 1 - tak, 0 - nie*/
    double scale;          /*skala*/
    BOOL print_window ;        /*wydruk okna*/
    BOOL print_sheet ;         /*wydruk arkusza*/
    char *sheet_adr ;           /*adres bloku arkusza*/
    BOOL ink_plotter ;        /*ploter atramentowy*/
    char port [MaxTextLen] ;
    double pen_width;      /*grubosc pisaka do wypelnien*/
    BOOL fixed_name;
    BOOL page_size;
    BOOL color_print;
    BOOL color_255;
    int tab_pen_speed [MAXNPEN];  /*tablica predkosci pisakow*/
    double tab_line_width_ink [8];        /*tablica grubosci linii*/
    int number_of_pen;
    T_Pen_Line tab_pen_number [MaxNColor];  /*tablica numerow pisakow dla*/
				      /* poszczegolych kolorow i typow linii*/
    T_Pen_Color tab_pen_color [MaxPColor];  /*tablica wartosci kolorow pisakow*/
}
T_Plt_Ini_Date, *T_PTR_Plt_Ini_Date ;

static double akt_pen_width;



#ifdef __cplusplus
extern "C" {
#endif

extern BOOL Plt_Draw_Param (char *, T_PTR_Plt_Config *, T_PTR_Plt_Ini_Date * ) ;
extern BOOL Draw_to_Plt_Proc (T_PTR_Plt_Config, T_PTR_Plt_Ini_Date) ;

#ifdef __cplusplus
}
#endif
