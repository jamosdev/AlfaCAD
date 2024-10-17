
#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char _dac_g256[][3];    /* 256 shading dac values */
extern unsigned char _dac_normal[][3];  /* 256 standard colors    */

extern void setrgbdefaults(void);
extern void setrgbgray256(void);

#ifdef __cplusplus
}
#endif

