#ifndef LIBFUN_PL_H_O_PRN_CUPS_H
#define LIBFUN_PL_H_O_PRN_CUPS_H

typedef struct
{
    char *printer_name;
    int width;  //in hundreds of mm
    int length;
    int bottom;
    int left;
    int right;
    int top;
} CUPS_PRINTERS;

#endif //LIBFUN_PL_H_O_PRN_CUPS_H
