
#ifdef asdawsdsd
typedef enum
{
  GN_Display = 0,
  GN_Printer,
  GN_Ploter,
}T_Param_Group;

char *Group_Name [] =
{
  "Ekran",
  "Drukarka",
  "Ploter",
} ;

int No_Group_Name = sizeof (Group_Name) / sizeof (Group_Name [0]);

typedef enum
{
  Prn_type = 0,
  Prn_line_feed,
  Prn_mode_draft,
  Prn_density_draft,
  Prn_mode_normal,
  Prn_density_normal,
  Prn_mode_double,
  Prn_density_double,
  Prn_margin,
  Prn_dot_width,
  Prn_line_thinest_width,
  Prn_line_thin_width,
  Prn_line_norm_width,
  Prn_line_thick_width,
  Prn_line_thickest_width,
}T_Param_Prn;


char *Param_Prn [] =
{
  "Typ Drukarki",
  "Przesow Pionowy216",
  "Druk Draft",
  "Gestosc Draft",
  "Druk Normalny",
  "Gestosc Normalna",
  "Druk Dokladny",
  "Gestosc Dokladna",
  "Margines",
  "Srednica Punktu",
  "Szerokosc Linii Bardzo Cienkiej",
  "Szerokosc Linii Cienkiej",
  "Szerokosc Linii Grubej",
  "Szerokosc Linii Bardzo Grubej",
  "Szerokosc Linii Najgrubszej",
};
int No_Param_Prn = sizeof(Param_Prn) / sizeof(Param_Prn[0]);

#endif

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL Get_Private_Profile_Strings (T_Fstring, BOOL (*)(T_Fstring, T_Fstring) ) ;

extern BOOL Add_Private_Profile_Group (T_Fstring, BOOL (*add_value)(FILE *)) ;

#ifdef __cplusplus
}
#endif
