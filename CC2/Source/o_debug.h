
#ifdef __cplusplus
extern "C" {
#endif

extern void Set_Version (int);
extern void Normalize_Objects (long_long, long_long, int );
extern void Normalize_Object (NAGLOWEK *nag);
extern BOOL Check_Text (NAGLOWEK *nag, BOOL b_correct);
extern BOOL Check_Object (NAGLOWEK *nag, BOOL b_correct);
extern BOOL Check_Objects (long_long off, long_long offk, BOOL b_file);
extern BOOL Check_Next_Object (void *ptr_ob);
extern BOOL Check_Blocks (long_long off, long_long offk);
extern void test_blok (FILE *stru);
extern int Test_Obiekts_Report (void);
extern BOOL Test_Object (void * ptr);
extern void Trace_Object (void *ptr_obiect);
extern void Open_File_Trace (void);
extern void Close_File_Trace (void);

#ifdef __cplusplus
}
#endif
