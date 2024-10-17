
//#include "o_xms.h"
#include "glyph.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////


#define OFFEMPTY   -1

#define NUM_CHAR_MAX 1920 //226
#define MAXFILENAME_OLD   12  //32
#define MAXFILENAME   34 ////12  //32
#define MAXFILENAMEDXF 32
#define COMMLEN 100
#define FONTNAMELEN_OLD 13      //12 //32
#define FONTNAMELEN 33 ////13      //12 //32
#define FONTNAMELENDXF 32
#define MAXCHARNO 1920 //256
#define MaxNumberTextStyle 128
#define MaxNumberTextStyleDXF 512 //255 //128

#define FONTVER_LEN 17
#define FONTVER    "ALF-CAD FONT V1.1"
#define FONTCOMMENT     "ALF-CAD FONT V1.1\n ALFAX WROCLAW 1993\n"


#define FONTVERNEW "ALFACAD FONT V1.3"
#define FONTCOMMENTNEW  "ALFACAD FONT V1.3\n FOR ENGINEERS 2023\n"

#define ITALICS_ANGLE 15

typedef int BOOL;


	typedef struct
	{
		int 		b_xms;			/*alokacja w xms czy na dysku*/
		unsigned 	handle;            	/*handle do xms lub pliku gdy otwarty*/
		char 		file_buf[13];         /*nazwa pliku gdy alokacja na dysku*/
		long 	    alloc_size;		/*rozmiar zaalokowanej pamieci*/
		BOOL 		b_fopen;		/*TRUE gdy plik otwarty*/
	}
	T_XMS_Alloc_Param, *T_Lp_XMS_Alloc_Param;

enum FONT_PLACE
{
   NO_PLACE = 0, 	/*brak fontu w pamieci*/
   PLACE_XMS = 1,	/*font jest zaladowany do pamieci EMB*/
   PLACE_BUF = 2 , 	/*font jest w buforze pamieci podstawoej*/
   PLACE_BUF_FONT = 4, 	/*font jest w buforze fontow*/
} ;

typedef struct
{
#ifndef LINUX
  long /*int*/ i_offset ;		/*polozenie wzorca znaku od poczatku wzorcow*/
  long /*char*/ vectorsno ;		/*liczba wektorow znaku*/
#else
    unsigned int i_offset;		/*polozenie wzorca znaku od poczatku wzorcow*/
    unsigned int vectorsno;		/*liczba wektorow znaku*/
#endif
}
T_Font_Off ;


typedef struct 
{
  char comment [COMMLEN] ; 	/*jeden lub kilka wierszy opisu pliku*/
  unsigned check_sum ;		/*suma kontrolna*/
  unsigned flags ;		/**/
}
T_Font_File_Header ;

typedef struct
{
	char font_name[FONTNAMELEN_OLD];/*nazwa fontu*/
	char font_acad_name[MAXFILENAME_OLD];/*nazwa pliku fontu dla acad'a*/
	unsigned font_size;		/*rozmiar wzorcow*/
	unsigned char num_char ;	/*liczba znakow w foncie*/
	unsigned char first_char ;	/*kod pierwszego znaku*/
	unsigned char height;	/*wysokosc*/
	unsigned char vert_margin;	/*margines w pionie*/
	char margin_char;   		/*odleglosc miedzy wzorcami liter*/
	double last_height;		/*w jednostkach wewnetrznych*/
	double font_aspect;		/*ws. korygujacy wsp. fontu do wsp. wew. programu*/
	/*-----------------*/
	unsigned place_xms : 1;      /*font jest zaladowany do pamieci EMB*/
	unsigned place_buf : 1;      /*font jest w buforze pamieci podstawoej*/
	unsigned place_buf_font : 1; /*font jest w buforze fontow*/
	unsigned type : 8;
	unsigned reserve : 5;
	T_XMS_Alloc_Param s_alloc_param;
	unsigned char *ptrsz_widths;  /*adres tablicy szerokosci znakow*/
	T_Font_Off * ptrs_off; 	/*adres tablicy offsetow*/
	char *ptrsz_font;            /*adres wzorcow znakow*/
}
T_Font_Header_Old;

#pragma pack(1)

typedef struct
{
  char font_name [FONTNAMELEN] ;/*nazwa fontu*/
  char font_acad_name [MAXFILENAME] ;/*nazwa pliku fontu dla acad'a*/
  unsigned font_size : 32;		/*rozmiar wzorcow*/
  unsigned int num_char ;	/*liczba znakow w foncie*/
  unsigned int first_char ;	/*kod pierwszego znaku*/
  unsigned char height ;	/*wysokosc*/
  unsigned char vert_margin ;	/*margines w pionie*/
  char margin_char ;   		/*odleglosc miedzy wzorcami liter*/
  double last_height ;		/*w jednostkach wewnetrznych*/
  double font_aspect ;		/*ws. korygujacy wsp. fontu do wsp. wew. programu*/
  float letter_spacing;
  /*-----------------*/
  unsigned place_xms : 1 ;      /*font jest zaladowany do pamieci EMB*/
  unsigned place_buf : 1 ;      /*font jest w buforze pamieci podstawoej*/
  unsigned place_buf_font : 1 ; /*font jest w buforze fontow*/
  unsigned type : 8;
  unsigned reserve : 5 ;
  //GLYPH_FACE *face;
  T_XMS_Alloc_Param s_alloc_param ;
  unsigned char *ptrsz_widths ;  /*adres tablicy szerokosci znakow*/
  T_Font_Off * ptrs_off ; 	/*adres tablicy offsetow*/
  char *ptrsz_font ;            /*adres wzorcow znakow*/
}  
T_Font_Header ;
#pragma pack()
typedef struct
{
	char font_name[FONTNAMELEN_OLD-1];
	unsigned char number;
} FontStyle40;

typedef struct
{
	char font_name[FONTNAMELEN];
	unsigned char number;
	unsigned char type;
} FontStyle;


typedef struct
{
	unsigned char new_no[MaxNumberTextStyle];
	unsigned char type[MaxNumberTextStyle];
	BOOL zeroing[MaxNumberTextStyle];
} FontTable;

typedef struct
{
  char font_acad_name [MAXFILENAMEDXF] ;/*nazwa zbioru fontu acad*/
  char font_alf_name [FONTNAMELEN] ;/*nazwa odpowiednika fontu w alfie*/
  double df_width_factor ;
}  
T_Font_Header_DXF ;

typedef struct
{
  char font_acad_name [FONTNAMELENDXF] ;/*nazwa fontu acad*/
  unsigned int font_number ;/*numer odpowiednika fontu w alfie*/
  unsigned char flags;
  double fixed_height;
  double width_factor ;
  unsigned char italic ;
  unsigned char generation_flags;
}  
T_Font_Header_DXF_TABLE ;




typedef struct
{
  double df_width_factor ;
  double df_width_line ;
}
T_Font_Style ;

extern int WhNumberTextStyle ;
extern int WhNumberTextStyle0 ;
extern int WhNumberTextStyleDXF;

extern T_Font_Style s__Fonts_Style [MaxNumberTextStyle] ;
extern T_Font_Header *PTRS__Text_Style [MaxNumberTextStyle] ;
extern FontTable PTRS__Font_Table;
extern T_Font_Header_DXF PTRS__Text_Style_DXF [MaxNumberTextStyleDXF] ;
extern T_Font_Header_DXF_TABLE PTRS__Text_Style_DXF_TABLE [MaxNumberTextStyleDXF] ;

#ifdef __cplusplus
}
#endif