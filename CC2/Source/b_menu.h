#ifdef __cplusplus
extern "C" {
#endif

extern void Test_Menu (TMENU *) ;
extern void Set_Global_Menu_Flags (int);
extern int  Get_Global_Menu_Flags (void);
extern void  *get_mem_menu(void);
extern void  *getmem(unsigned);
extern void free_mem(void);
extern unsigned long_long get_free_mem_size (int way);
extern void drawp(TMENU *);
extern unsigned Get_Menu_Image_Size (TMENU *);
extern int inkeys(TMENU *, BOOL search_ok);
extern int  getwsp(TMENU *); 
extern int getwsp3(TMENU *);
extern int  getwsp1(TMENU *);
extern EVENT *GetEvent(TMENU *);

typedef struct
{
	int x1;
	int y1;
	int x2;
	int y2;
}  FRAME_COORDS;

typedef struct
{
	FRAME_COORDS frame[5];
} FRAMES;

#ifdef __cplusplus
}
#endif


