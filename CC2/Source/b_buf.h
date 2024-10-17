typedef struct
{
  void *ptr_table ;		/*adres tablicy */
  int i_size ;			/*rozmiar tablicy*/
  int i_size_alloc ;		/*aktualna alokacja*/
  int i_unit_size ;		/*rozmiar jednostki*/
  int i_d_alloc ;               /*wielkosc dealokacji*/
}
T_Units, *T_PTR_Units ;


#ifdef __cplusplus
extern "C" {
#endif


extern unsigned long_long Get_Free_Physical_Memory(void);
extern unsigned long_long Get_Free_Virtual_Memory(void);
extern void InitBufPCX(unsigned long buffer_size);
extern void FreeBufPCX(void);
extern void InitImages (void) ;
extern void InitBuffers (void) ;
extern void DoneBuffers (int dwg_no) ;
extern char *NewBuffer (char **) ;
extern void DisposeBuffer (char *) ;
extern long GetBufferSize (char *) ;
extern long_long GetFreeMemSize (void) ;
extern int SetBufferSize (char *, long) ;
extern long_long Get_Buf_Mem_Size (void) ;
#ifdef __cplusplus
  extern void h_free (void *block) ;
  extern BOOL h_realloc (T_PTR_Units, int = 0) ;
  extern BOOL h_alloc (char **block, long size) ;
#endif

#ifdef __cplusplus
}
#endif
