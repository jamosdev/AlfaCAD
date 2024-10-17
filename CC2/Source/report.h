//
// Created by Marek on 1/18/24.
//

#ifndef LIBFUN_PL_H_REPORT_H
#define LIBFUN_PL_H_REPORT_H

#include <stdio.h>

#define dbglevl_debug 1
#define dbglevl_verbose 2
#define dbglevl_ERROR 3
#define Error 4

void report(int level, char *message)
{
    printf("%s\n", message);
    fflush(stdout);
}

#endif //LIBFUN_PL_H_REPORT_H
