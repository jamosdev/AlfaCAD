
#define Max_No_Spec 16
#define Max_Spec_Value MaxTextLen
#define Max_Spec_Name3 16 
#define Max_Spec_Name 32
#define Max_Spec_Block 127

typedef struct
{
	char spec_value[Max_Spec_Value];
	char spec_name[Max_Spec_Name];
} T_spec_name;

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL Read_Spec1_1 (int, T_spec_name *, int) ;
extern BOOL Read_Spec (int, T_spec_name *, int) ;
extern BOOL Read_Spec_File (char *, T_spec_name *, BOOL) ;
extern BOOL Read_Spec_Block (char *, char *, int, char *, int, BOOL) ;
extern BOOL Save_Spec (int, T_spec_name *) ;
extern BOOL Save_Spec_File (char *, T_spec_name *) ;
extern BOOL Save_Spec_Block (char *, char *, char *) ;
extern void Ini_Spec_Param (void) ;
extern void Ini_Spec_Param_copy(void);
extern T_spec_name * Get_Local_Spec (void) ;
extern void Clear_Local_Spec (void) ;
extern void Edit_Spec (void) ;

#ifdef __cplusplus
}
#endif
