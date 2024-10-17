#ifdef __cplusplus
extern "C" {
#endif

extern void mvcurbpT (unsigned);
extern void Get_Text_Scale (TEXT *, double *, double *);
extern int Get_Char_Matix_Len (unsigned intchar, int);
//extern int Get_Char_Matix_Len_ (char, int);

#ifdef __cplusplus
extern long Get_Text_Matix_Len (TEXT *, char* = NULL);
extern double Get_Text_Len (TEXT *, char* = NULL, double font_scale = 1.0, int font_index=0, int* =NULL, int* =NULL, double* =NULL, int* =NULL);
extern double Get_Text_Len_ (TEXT *, char* = NULL, double font_scale = 1.0, int font_index=0, int * =NULL, int * =NULL);
#endif

extern double Get_TextLen (TEXT *ptrs_text, char *ptrsz_t) ;
extern void Clear_Fonts_Flags (BOOL, BOOL) ;
extern BOOL Load_Font (int) ;
extern void outtextxy_w_ (TEXT *, int);
extern void outtextxy_w (TEXT *, int);
extern void outtextxy_wP_ (TEXT *, int);
extern void outtextxy_wP (TEXT *, int);


#ifdef __cplusplus
}
#endif

