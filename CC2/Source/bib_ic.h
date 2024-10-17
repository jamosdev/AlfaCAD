/*----------------------------------------------*/
typedef void  * TFF;
typedef void  * TFH;
#define ICF 101

/*blok danych globalnych */
typedef
  struct  {
   int xp,yp,xk,yk,Ky; /*  os Y do gory Ky=-1 */
   double skala,sk_x;
   double WD,Pi;
   double krok_s,krok_g;
   int grid_,X_Y_kursora,Komunikat_R,Komunikat_R0,
   Error,orto,Driver,Mode,Dzwonek;
   double Xp,Yp,Xk,Yk,Xmax,Ymax,Xmin,Ymin,
   Y_max,X_max;
   double Xd,Yd,X2d,Y2d;
   double X,Y;
   int maxX,maxY,maxXr,maxYr;
   int paper_kom,ink_kom;
   int wyj,BlokK;
   char  *dane;
   long dane_size;
   int (*SERV[SVMAX])(TMENU  *);
   void (*MVCUR)(int x,int y);
   void (*CUR_OFF)(double, double);
   void (*CUR_ON)(double, double);
   int (*KLS)(void);
   void (*REDDOD)(void);
   void (*MPINI)(int n);
   unsigned long buf_mem_menu;
   int Warstwa;
   char *bufor_makra, *aktmakro, *mkbuf, *mbufmx;
   LAYER Layers[MAX_NUMBER_OF_LAYERS];
   int FormatX,FormatY;
   double SkalaF ;
   double DokladnoscF, Jednostki;

   char zbior_danych[MAXPATH];
   char zbior_danych_2[MAXPATH];
   char add_zbior_2;
   ZMIENNE zmwym;
   int BlokM;
   char  *ADP,  *ADK;
   BLOK  *LASTb;
   SEL sel;
   void (*FUN[ICF])(void);
   void (*ICFUN[ICF])(void);
          } COMMON;

/*----------------------------------------------*/

typedef
  struct {
/*funkcje okienkowe*/
int (*getwsp)(TMENU *menu);
char (*inkeys)(void);
void (*drawp)(TMENU *menu);
int (*getwsp1)(TMENU *menu);
int (*getwsp3)(TMENU *menu);

/*bib_e*/
void (*pozycja_kursora)(void);
void (*out_cur)(double X,double Y);
void (*komunikat)(int);
void (*komunikat_str)(char  *st);
void (*komunikat0)(int);
void (*komunikat0_str)(int, char  *st);
int (*pikseleDX)(double jednostki);
int (*pikseleDY)(double jednostki);
int (*pikseleX0)(double jednostki);
int (*pikseleY0)(double jednostki);
double (*jednostkiX)(int piksele);
double (*jednostkiY)(int piksele);
double (*jednostkiplt)(double mmplt);
double (*milimetryob)(double jednostki);
double (*milimetryobx)(double jednostki);
double (*milimetryoby)(double jednostki);
void (*okno_r)(void);
void (*okno_all)(void);
void (*grid_off)(void);
void (*grid_on)(void);
void (*cursorT_off)(int x,int y);
void (*cursorT_on)(int x,int y);
int (*read_esc)(char  *,int,int);
void (*d_2d)(void);
int (*linestyle)(int typ);
void (*redrow)(void);
void (*menu_par_new)(char * pole, const char * par);
void (*dzwonek)(void);
void (*zwolnienie_pamieci)(void);
int (*korekta_parblok)(void  *st,long n);
char *(*dodaj_obiekt)(BLOK * adb,void  *ad);
void (*obiekt_tok1)(char *adr,char  *adrk,char **ad,int obiekt);
void (*obiekt_tok)(char *adr,char  *adrk,char **ad,int obiekt);
void (*Xp_Yp)(void);

/*bib_e1*/
void (*usun_obiekt)(void  *);
void *(*korekta_obiekt)(void  *ad,void  *obiekt);
void (*zmien_atrybut)(char  *,char  *,int ,int );
void (*usun_blok)(char  *,char  *);
void (*out_kolo)(OKRAG *);
void (*out_wypelnienie)(WIELOKAT *);
void (*outokno)(OKNO *O,double dx,double dy);

/*bib_text*/
void (*outtextxy_r)(int x,int y,char  *textstring);
void (*outtext_r)(char  *textstring);
void (*outtextxy_w)(TEXT  *t,int mode);
void (*outtextxy_wP)(TEXT  *t,int mode);
/*bib_line*/
void (*outline)(LINIA  *L,int mode,int pl);
void (*outlineor)(LINIA  *L,int mode,int pl);
void (*parametry_lini)(LINIA  *L,PLINIA *PL);
void (*clear_parametry_lini)(void);

/*bib_zb*/
int (*czytaj_zbior)(char *, BOOL, BOOL, BOOL);
int (*pisz_zbior)(char *, int);

/*bib_sel */
void (*cursel_off)(double x,double y);
void (*cursel_on)(double x,double y);
int (*punkt_w_prostokacie)(double x,double y);
int (*linia_w_prostokacie)(LINIA *ad);
int (*tekst_w_prostokacie)(TEXT *ad);
int (*luk_w_prostokacie)(LUK *ad);
int (*okrag_w_prostokacie)(OKRAG *ad);
int (*wielokat_w_prostokacie)(WIELOKAT *ad);
int (*linia_wybrana)(LINIA *ad);
int (*tekst_wybrany)(TEXT *ad);
int (*luk_wybrany)(LUK *ad);
int (*okrag_wybrany)(OKRAG *ad);
int (*wielokat_wybrany)(WIELOKAT*ad);
TFF  (*select_w)(unsigned *typ, void **adr);
TFF  (*select)(unsigned *typ, void **adr);
TFH  (*select_edwym)(unsigned *typ);
void (*oknoS)(double X1,double Y1,double X2,double Y2);
void (*out_sel)(double X,double Y);
int (*sel_t)(void);
int (*sel_d)(void);

/*bib_blok*/
void (*transformacja_blok)(char  *adr,char  *adrk,double x,double y,double k1,double k2,int trans);
void (*rysuj_obiekt_)(void *ad, int mode,int kolor);
void (*rysuj_obiekt)(void *ad, int mode,int kolor);
void (*mvcurbp)(unsigned i);
void (*blokzap)(char  *adp,char  *adk,int atrybut,int mode, int kolor);
void (*out_blok)(void);
void (*out_blok1)(double x,double y,double k1,double k2,int trans);
int (*dodaj_blok)(char  *adr,char *adrk,double x,double y,double k1,double k2,int trans);
void (*undo_blok)(void);
void (*Global_Undo)(void);
void (*blok)(int (*DZI)(void *), int (*ODZI)(void *),
		 void (*REDROWd)(void),void (*COMND[])(void));

/*bib_arc*/
void (*DrawCircle)(int Xr,int Yr,int R);
void (*DrawArc)(int Xr,int Yr,double sta,double ea,int R);

/*bib_menu*/
void (*menupini)(TMENU *menu,char *st,char cod);
void (*getmenupini)(TMENU **menu,char *st,char *cod);

/*bib_snap*/
void (*koniecL_)(double *x, double *y, void *adr);
int (*przeciecieLL_)(double *x, double *y, void *adr, void *adr1);
int (*przeciecieLO_)(double *x, double *y, void *adr, void *adr1);
int (*przeciecieOO_)(double *x, double *y, void *adr, void *adr1);

/*graphics.h*/
void  (*setwritemode)(int mode);
void  (*setlinestyle)(int linestyle,unsigned upattern,int thickness);
void  (*setcolor)(int color);
void  (*rectangle)(int left,int top,int right,int bottom);
void  (*setfillstyle)(int pattern,int color);
void  (*bar)(int left,int top,int right,int bottom);
void  (*moveto)(int x, int y);
int   (*getx)(void);
int   (*gety)(void);
  } FUNKCJE;

/*----------------------------------------------*/
