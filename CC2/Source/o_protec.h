#define RIGHTMARGIN 	64
#define USERTITLE 	13
#define SERIESTITLE 	8
#define PROT_KEY_LEN 	18
#define PROT_KEY 	"11122233fertyyjjlp"
#define USER_NO	11

static int XOR_MATRIX[90]={11,21,31,41,51,61,71,81,91,12,
                           22,32,42,52,62,72,82,92,13,23,
                           33,43,53,63,73,83,93,14,24,34,
                           44,54,64,74,84,94,15,25,35,45,
                           55,65,75,85,95,16,26,36,46,56,
                           66,76,86,96,17,27,37,47,57,67,
                           77,87,97,18,28,38,48,58,68,78,
                           88,98,19,29,39,49,59,69,79,89,
                           99,10,20,30,40,50,60,70,80,90};
static int XOR_MATRIX1[90]={15,25,35,45,55,65,75,85,95,16,
                           26,36,46,56,66,76,86,96,17,27,
                           37,47,57,67,77,87,97,18,28,38,
                           48,58,68,78,88,98,19,29,39,49,
                           59,69,79,89,99,10,20,30,40,50,
                           60,70,80,90,11,21,31,41,51,61,
                           71,81,91,12,22,32,42,52,62,72,
                           82,92,13,23,33,43,53,63,73,83,
                           93,14,24,34,44,54,64,74,84,94};

/*typedef int                 BOOL;*/

typedef struct
{
  int b_use ; 			/*czy uzyto struktury*/
  int off ;			/*offset  xor_matrycy*/
  unsigned char rom_mdr [6] ;   /*data bios'a ^ XOR_MATRIX*/
}
T_Rom_Mdr ;


typedef struct
{
  unsigned char sz_key [PROT_KEY_LEN] ;
  unsigned b_user_name : 1 ; 	/*czy wpisano nazwe uzytkownika*/
  unsigned b_work      : 1 ; 	/*czy wersja robocza nie zabezpieczona*/
  unsigned b_compare   : 1 ;	/*czy wlasciwa data bios'a, dla wersji handlowej*/
  unsigned b_prot      : 1 ;	/*czy wpisano date bios'a dla wersji handlowej*/
  unsigned char sz_user_name [80] ;
  char sz_series [80] ;
  T_Rom_Mdr rom_mdr_tab [USER_NO] ; /*tablica dat bios'a*/
}
T_Prot_Date ;

/*#define DefProtDate = {PROT_KEY, 0, 0, 0, 0, "", "                         U�ytkownik : ", "                         Seria : "} ;*/


extern char *Get_Xor_Matrix (void) ;
extern void Out_Prot_Err (int err) ;
extern int File_Prot_Proc (char *ptrsz_file, int (*proc)(char*), int b_save);
extern int File_Prot  (char *, int (*proc)(char*)) ;
extern char* Get_Date (int off) ;
extern void Protection (char *) ;
extern void Put_Data_To_File (char * ) ;
extern int Check_Prot (void) ;
extern int Get_New_Off_Xor (int) ;

