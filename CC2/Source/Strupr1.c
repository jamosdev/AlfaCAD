/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <forwin.h>
#include <ctype.h>
#include <string.h>

char *strupr2(char *_s)
{
  char *rv = _s;
  while (*_s)
  {
    if ((unsigned char)(*_s) < 128) *_s = toupper(*_s);
    _s++;
  }
  return rv;
}
