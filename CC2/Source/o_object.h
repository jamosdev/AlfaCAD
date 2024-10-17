#define OFF_NULL -1l	/*offset, odpowiednik NULL-a*/

enum OBJECT_TOK_MODE {TOK_LAYER_ON = 0,
		      TOK_LAYER_ALL = 1,  /*wszystkie obiekty z wyjatkiem usunietych lub zlych*/
		      TOK_ALL = 2} ;      /*wszystkie obiekty lacznie z usunietymi i zlymi*/

#ifdef __cplusplus
extern "C" {
#endif

extern int Get_Tok_Mode (void) ;
extern int korekta_parblok(void *st,long n) ;
extern char *dodaj_obiektFD(BLOK *adb, int handle) ;
extern char *Add_Object (BLOK **, void *) ;
extern char *Add_Block_Object (BLOK **, void *, long) ;
extern char* Add_Block_Object_Ex(BLOK**, void*, long);
extern char *dodaj_obiekt(BLOK * adb,void *ad) ;
extern char *dodaj_obiekt_reversed(BLOK * adb,void *ad) ;
extern char * Copy_Object (char *adr)  ;
extern char * Copy_ObjectB (BLOK ** ptrptr_adb, char *adr);
extern void obiekt_tok_all (char  *adr, char *adrk, char  **ad, int obiekt);
extern void obiekt_tok1(char *adr,char  *adrk,char **ad,int obiekt);
extern void obiekt_tok2(char *adr,char  *adrk,char **ad,int obiekt);
extern void obiekt_tok(char *adr,char  *adrk,char **ad,int obiekt);
extern void ObiektTok (long_long *off, long_long offk, long_long *ad, int obiekt);
extern void Object_Tok_All (long_long *off, long_long offk, long_long *ad, int obiekt);
extern void *Object_Tok (long_long *, long_long, long_long *, int, int) ;
extern void Usun_Object (void *ad, BOOL b_simple);
extern void usun_obiekt(void *ad);
extern void *Change_Object (void *ad, void *obiekt, BOOL b_simple);
extern void *korekta_obiekt (void *ad, void *obiekt);
extern long_long *Change_Description_Block (BLOK *, void *, int) ;
extern void zmien_atrybut(char  *adr,char  *adrk,int aold,int anew);
extern void zmien_atrybut_undo(char *,char * );
extern void usun_blok (char  *adr, char  *adrk);
extern int dodaj_blok (char  *adr,char  *adrk,double x,double y,double k1,double k2,int trans);
extern BOOL Add_Block (char  *, char  *, long *, double, double, double, double, double, double, double, double, int);
extern void undo_blok(void);
extern void Global_Undo(void);

/*o_object1.c*/
extern BOOL Check_if_Empty_Block (BLOK *) ;
extern BOOL End_Arc (double *x, double *y, double x0, double y0, LUK *l);
extern BOOL End_Elliptical_Arc_XY(double *x, double *y, double x0, double y0, int numpoints, double xy[]);
extern BOOL End_Elliptical_Arc(double *x, double *y, double x0, double y0, ELLIPTICALARC *ea);
extern int Cmp_Arc_Angle (double, double, double, double) ;
extern void Get_Text_Border (TEXT *ptrs_text, double *ptrdf_x,double *ptrdf_y, BOOL b_margin);
extern WIELOKAT *Text_to_Solid (TEXT *ptrs_text, WIELOKAT *ptrs_solid);
extern int Get_Rectangle_Type (WIELOKAT *ptr_w);
extern BOOL Get_Solid_Intersec (WIELOKAT *ptr_w,double *ptrdf_x,double *ptrdf_y,double *ptrdf_t1,double *ptrdf_t2);
extern BOOL Get_Rec_2TrAngle (WIELOKAT *ptr_w, WIELOKAT *ptr_w1, WIELOKAT *ptr_w2);
extern BOOL Get_Rec_Division(WIELOKAT* ptr_w, WIELOKAT* ptr_w1, WIELOKAT* ptr_w2);
extern void Normalize_Solid (WIELOKAT *ptr_w);
extern int Get_Polygon_Num (BLOK *ptrs_b);
extern BOOL Point_Arc ( double x, double y, LUK *l);
extern BOOL Point_Arc_Prec ( double x, double y, LUK *l, int i_precion);
extern void Arc_To_Points (LUK *l, double *x1, double *y1, double *x2, double *y2);
extern void Vector_Arc_To_Points (AVECTOR *v, double *x1, double *y1, double *x2, double *y2);
extern void SolidArc_To_Points (SOLIDARC *sa, double *x1, double *y1, double *x2, double *y2);
extern void Points_To_Arc (LUK *l, double x1, double y1, double x2, double y2);
extern void Points_To_Arc_Vector (AVECTOR *v, double x1, double y1, double x2, double y2);
extern void Points_To_SolidArc (SOLIDARC *sa, double x1, double y1, double x2, double y2);
extern void Redraw_Block (void);
extern BOOL check_if_hidden (char  *adp,char  *adk,int atrybut);
extern BOOL check_if_edit (char  *adp,char  *adk,int atrybut);
extern BOOL get_extend (char  **adp_l,char  **adk_l,int atrybut);
extern BOOL check_if_obiekt (char  *adp, char  *adk, int atrybut, int obiekt);

/*o_object2.c*/
extern void Set_Block_Change_Mode (void *, int ) ;
extern long_long Get_Size_Block (long_long , long_long );
extern void Set_Object_Temp_Flag (int , long_long , long_long );
extern void Set_Object_T2_Flag (int , long_long , long_long );
extern void Ini_Global_Object (void);
extern int Get_Current_Color (void);
extern int Get_Width_Line (int );
extern int Get_Type_Line (int );
extern int Set_WidthL_to_Type (int , int );
extern int Set_TypeL_to_Type (int , int );
extern BLOK * Get_Common_Blok (void * , void *);
extern BLOK *LASTB(char  *);
extern BLOK* FIRSTB(char*);
extern BLOK *LASTB_A(char  *);
extern BLOK* FIRSTB_A(char*);
extern BLOK *Parent_Block (char  *);
extern double Get_Scale (double , double , double , double );
extern void parametry_lini (LINIA *,PLINIA *);
extern void *Add_Object_Set_Global_Ptr (BLOK ** , void *);
extern void Erase_Object_Set_Global_Ptr (void *);
extern void Erase_First_Objects (long_long );
extern void *Change_Object_Set_Global_Ptr (void *, void *);

#ifdef __cplusplus
}
#endif
