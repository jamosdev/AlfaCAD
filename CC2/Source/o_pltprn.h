
typedef struct
{
	double xy[8];
} PCX_SOLID;

typedef struct
{
	double xmin;
	double ymin;
	double xmax;
	double ymax;
} PCX_MM;


typedef struct
{
	double x_min;
	double y_min;
	double x_max;
	double y_max;
} Print_Rect;

typedef enum { LINE_MIN_WIDTH = -1, LINE_THINEST_WIDTH, LINE_THIN_WIDTH, LINE_NORM_WIDTH, LINE_THICK_WIDTH, LINE_THICKEST_WIDTH, TEXT_LINE_TYPE, TEXT_LINE_TYPE_THIN
} LINE_WIDTH;

#ifdef __cplusplus
extern "C" {
#endif

extern double Get_Line_Prn_Si (void);
extern double Get_Line_Prn_Co (void);
extern void Set_Line_Width (double);
extern void Set_Type_Drive (int, int, double, double, double);
extern void Set_Draw_Window (double, double, double, double);
extern BOOL Draw_Fill_Circle_To_Drive (OKRAG*);
extern BOOL Draw_Wielokat_To_Drive (WIELOKAT *, Print_Rect* window_to_print);
extern BOOL Draw_Solidarc_To_Drive (SOLIDARC *, Print_Rect* window_to_print);
extern BOOL Draw_Vector_To_Drive (AVECTOR *, Print_Rect* window_to_print);
extern BOOL Draw_Arc_To_Drive (LUK *);
extern BOOL Draw_Ellipse_To_Drive (ELLIPSE *);
extern BOOL Draw_EllipticalArc_To_Drive (ELLIPTICALARC *);
extern BOOL Draw_pcx_8_To_Drive(B_PCX *, int t_drive);
extern void solid04_prn_old(double, double, double, double, int, double, double, BOOL, BOOL);
extern void solid04_prn(PCX_SOLID *pcx_s, COLOR_, double, double, BOOL, BOOL);
extern BOOL Draw_Line_To_Drive ( LINIA *);
extern BOOL Draw_Point_To_Drive ( T_Point *);
extern BOOL Draw_Tekst_To_Drive(TEXT *, int, int, int /*, double*/);
extern BOOL Ini_Output_Device (char *, BOOL, int, BOOL) ;
extern int Write_To_Device (void *buf, unsigned int len) ;
extern int Close_Output_Device (void) ;
extern BOOL plt_mark_char(unsigned char zn);
extern BOOL plt_pen_width_ink (int , double);
extern BOOL write_ter (void);

#ifdef __cplusplus
}
#endif
