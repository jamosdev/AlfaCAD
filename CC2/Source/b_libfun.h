
enum BERROR
{ NO_ERR = 0 ,
  ERR_BLOCK_SIZE = 1,
  ERR_NOMEM = 2,
} ;


#ifdef __cplusplus
extern "C" {
#endif

extern BOOL Check_Break_Key (void) ;
extern int Get_Error_No (void) ;
extern void Set_Error_No (int) ;
extern BOOL Check_Attribute (int, int) ;


#ifdef __cplusplus
}
#endif
