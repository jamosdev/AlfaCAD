
enum DE_VAL {DE_Draw = 0,	/*rysuj elipse*/
	     DE_Add,            /*dodaj segmenty elipsy do bloku*/
	     DE_Add_SGP,        /*dodaj segmenty elipsy do bloku, ustaw globalne pointer'y*/
	     DE_ADD_Ell_Arc_SGP,/*dodaj segmenty luku elipsy do bloku, ustaw globalne pointer'y*/
	     DE_Add_Ell_Fill_SGP} ; /*dodaj segmenty wypelnionej elipsy
				      do bloku, ustaw globalne pointer'y*/

#ifdef __cplusplus
extern "C" {
#endif

extern void Set_Ell_Verno (int);
extern int Get_Ell_Verno (void);
extern void Set_Ell_Angle (int);
extern int Get_Ell_Angle (void);
extern BOOL Make_Ellipse (double df_xc, double df_yc, double df_xaxis, double df_yaxis, double df_angle, int i_mode, BLOK **ptrptr_adb, void *ptr_ob, int i_type, int obiektt2, int type, int translucency, int kolor, int kolor0);
extern BOOL Make_EllipticalArc (double, double, double, double, double, double, double, int, BLOK **,void *,int, int ,int, int, int, int, int);
extern BOOL Make_Ellipse_Arc (double,double,double,double, BLOK**, void *, int, int);

#ifdef __cplusplus
}
#endif
