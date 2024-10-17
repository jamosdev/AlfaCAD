
#ifdef __cplusplus
extern "C" {
#endif

extern void oknoS(double x1,double y1,double x2,double y2) ;
extern void cursel_off(double x,double y) ;
extern void cursel_on(double x,double y);
extern double Get_Point_Size (void);
extern void Set_Point_Size (double df_ps);
extern BOOL Get_Point_View (void);
extern void Set_Point_View (BOOL b_pv);
extern int punkt_w_prostokacie(double x, double  y);
extern int linia_w_prostokacie(LINIA *ad);
extern int okrag_w_prostokacie(OKRAG *ad);
extern int linia_wybrana(LINIA *ad);
extern int vector_wybrany(AVECTOR *ad);
extern int tekst_wybrany(TEXT *ad);
extern int luk_wybrany(LUK *ad);
extern int luk_w_prostokacie(LUK *ad);
extern int solidarc_w_prostokacie(SOLIDARC *ad);
extern int prostokat_luk(LUK *ad);
extern int prostokat_solidarc(SOLIDARC *ad);
extern int prostokat_ellipticalarc(ELLIPTICALARC *ad);
extern int Point_Selected (T_Point *ptrs_point);
extern int Vector_Selected(AVECTOR *ptrs_vector);
extern int Point_in_Rectangle (T_Point *ptrs_point, int dwc);
extern int okrag_wybrany (OKRAG *ad);
extern BOOL Check_Draw_Pieslice (OKRAG *ad);
extern int wielokat_wybrany(WIELOKAT *w);
extern BOOL Check_DArea_in_Last_Solid (void);
extern BOOL Point_in_Solid (WIELOKAT *ptr_w, double x, double y);
extern void out_sel(double, double);

#ifdef __cplusplus
}
#endif
