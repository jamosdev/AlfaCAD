
#ifdef __cplusplus
extern "C" {
#endif

extern BOOL Copy_File_Nb (FILE* fdest, FILE* fsrc, long nbyte);
extern BOOL Copy_File (char *, char *) ;
extern char *Set_Full_File_Name (char *, char *) ;
extern char *Current_Directory (int, char *) ;

extern BOOL Set_File_Attrib (char *, int) ;
extern char * AddBackslash (char *) ;
extern BOOL file_bak (char *, char *) ;
extern char *File_Tmp(char *, char *) ;
extern char *File_Ext(char *, char *) ;
extern char *File_New_Ext (char *, char *) ;
extern long Get_Disk_Free_Space  (char *) ;
extern void Del_Backslash (char *) ;

#ifdef __cplusplus
}
#endif
