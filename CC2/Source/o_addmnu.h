
#ifdef __cplusplus
extern "C" {
#endif


extern int Change_Orto (void) ;		
extern int Choose_Layer_1 (void);
extern int Choose_Layer_2 (void);
extern int Choose_Layer_3 (void);
extern int Choose_Layer_4 (void);
extern int Choose_Layer_5 (void);
extern int Choose_Layer_6 (void);
extern int Choose_Layer_7 (void);
extern int Choose_Layer_8 (void);
extern int Choose_Layer_9 (void);
extern int Choose_Layer_10 (void);
extern int Inc_Layer (void);
extern int Dec_Layer (void);
extern int All_Layers_On_(void);
extern int Reverse_Layers_(void);
extern int kolorL_(void);		/*Alt-F1*/
extern int Kopiuj_Ctrl_R(void); /*Ctrl_R*/
extern int ciagnij_f1 (void); /*F1*/
extern int typ_linii_(void);		/*Alt-F2*/
extern int grubosc_linii_(void);	/*Alt-F3*/
extern int Set_Layers_ (void);		/*Alt-F4*/
extern int Wez_warstwe_ (void) ;        /*Alt-F10*/
extern int Hide_Layers_ (void) ;        /*Alt-F12*/
extern int Wez_kolor_ (void) ;          
extern int Wez_typ_ (void) ;            /*Alt-F9*/
extern int osnap_ (void);
extern int koniecS_ (void);		/*Shift-F2*/
extern int koniec_ (void);
extern int srodek_ (void);
extern int przeciecie_ (void);
extern int centrum_ (void);
extern int prostopadle_ (void);
extern int stycznie_  (void);
extern int najblizszy_ (void);
extern int Point_Sel_ (void);		/*Shift-F9*/
extern int JumpW_ (void);
extern int JumpB_ (void);
extern int Point_Measure_ (void);	/*Alt-F5*/
extern int Dist_Measure_ (void);
extern int Pan_Shift_(void);
extern int Angle_Measure1_ (void);
extern int Calculator_Measure_ (void); 	/*Alt-F8*/

extern int SkalaZ1_ (void)     ;	/*Ctrl F1   skala 1*/
extern int SkalaZ05_ (void)    ;	/*Ctrl F2   skala 0.5*/
extern int SkalaZ02_ (void)    ;	/*Ctrl F3   skala 0.2*/
extern int SkalaZ01_ (void)    ;	/*Ctrl F4   skala 0.1*/
extern int SkalaW_ (void)     ;	/*Ctrl F5   okno*/
extern int SkalaE_ (void)     ;	/*Ctrl F6   wszystko*/
extern int skala_format_ (void) ;	/*Ctrl F7   format*/
extern void skala_window(double xmin, double xmax, double ymin, double ymax, int dark);
extern void skala_window_p(double xmin, double xmax, double ymin, double ymax, int dark);
extern int SkalaZC_ (void)     ;	/*Ctrl F8   centrum*/
extern int SkalaR_ (void)      ;	/*Ctrl F9   odswiezenie*/
extern int last_view_ (void)   ;	/*Ctrl F10  ostatni*/
extern void Save_View (void) ;
extern int set_decrease_x (void) ;
extern int set_increase_x (void) ;
extern int set_decrease_y (void) ;
extern int set_increase_y (void) ;
extern int SkalaZ_Plus(int sclfct);
extern int SkalaZ_Minus(int sclfct);


#ifdef __cplusplus
}
#endif
