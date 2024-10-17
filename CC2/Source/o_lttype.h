
#ifdef __cplusplus
extern "C" {
#endif

extern char *Get_Ptr_Buf_Fonts (void);
extern int ReadTypyLinii (void);
extern int ReadTextStyle (void);
extern BOOL Free_Buf_Font_Mem (BOOL) ;

#ifdef __cplusplus
}
#endif

#define MaxNumberTextStyle 128  //same define in alffont.h

typedef struct
{
	char *file[MaxNumberTextStyle];
	char *face[MaxNumberTextStyle];
	const char *pdf_font_name[MaxNumberTextStyle];
	BOOL Alfa_loaded[MaxNumberTextStyle];
	BOOL PDF_embeded[MaxNumberTextStyle];
} TTF_font_files;
