#ifdef __cplusplus
extern "C" {
#endif

extern void Set_Edit_Vector (ESTR *, int (*)(BOOL)) ;
extern void Out_Edited_Draw_Param (ESTR *lps_et, BOOL out);
extern int dodajstr(ESTR *e);
extern void usunstr(int n);
extern int edycjastr(void);
extern int edycjastr_zn(char zn0);

#ifdef __cplusplus
}
#endif

