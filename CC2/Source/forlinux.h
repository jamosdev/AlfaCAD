
#ifndef ALF_FORLINUX_H
#define ALF_FORLINUX_H
#ifdef LINUX
extern char *strlwr(char *s);
extern char *strupr(char *s);
extern int stricmp(const char *a, const char *b);
extern int strnicmp(const char *a, const char *b, int n);
#ifdef __cplusplus
extern "C" {
#endif
extern char *strlwr_(char *s);
extern char *strupr_(char *s);
#ifdef __cplusplus
}
#endif

#endif
#endif //ALF_FORLINUX_H
