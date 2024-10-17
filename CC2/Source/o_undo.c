/*   ______   ___       ___         ____     ______  ____
*   /\  _  \ /\_ \    /'___\       /\  _`\  /\  _  \/\  _`\
*   \ \ \L\ \\//\ \  /\ \__/   __  \ \ \/\_\\ \ \L\ \ \ \/\ \
*    \ \  __ \ \ \ \ \ \ ,__\/'__`\ \ \ \/_/_\ \  __ \ \ \ \ \
*     \ \ \/\ \ \_\ \_\ \ \_/\ \L\.\_\ \ \L\ \\ \ \/\ \ \ \_\ \
*      \ \_\ \_\/\____\\ \_\\ \__/.\_\\ \____/ \ \_\ \_\ \____/
*       \/_/\/_/\/____/ \/_/ \/__/\/_/ \/___/   \/_/\/_/\/___/
*
*   A CAD
*
*   By Marek Ratajczak 2024
*
*   See readme_alfacad.txt for copyright information.
*
*/

#include<forwin.h>
#define ALLEGWIN
#include <allegext.h>
#include "bib_e.h"
#include "rysuj_e.h"

void * Find_Object (void * ob)
/*-----------------------------*/
{
  void *nag;
  long_long off=0, offk=dane_size, offob;
  void *find_ob = NULL;
  int len;
  int object_type;

  int a;

  if (ob == NULL)
  {
    return NULL;
  }
  nag = ob;
  object_type = ((NAGLOWEK*)nag)->obiekt;
  len = sizeof (NAGLOWEK) + ((NAGLOWEK*)nag)->n;
  ObiektTok (&off, offk, &offob, object_type);
  while (offob!=-1)
  {
      nag=(void*)(dane+offob);
      if ((memcmp (ob, nag, sizeof(NAGLOWEK) + ((NAGLOWEK*)nag)->n) == 0) &&
              (len == sizeof(NAGLOWEK) + ((NAGLOWEK*)nag)->n))
      {
          find_ob = nag;
          break;
      }
      //alternatively not taking into account color, type and layer for lines and arcs
      else if ((((NAGLOWEK*)nag)->obiekt==object_type)  && (memcmp ((void*)((char*)ob+sizeof(NAGLOWEK)+4), (void*)((char*)nag+sizeof(NAGLOWEK)+4), ((NAGLOWEK*)nag)->n-4) == 0) &&
          (len == sizeof(NAGLOWEK) + ((NAGLOWEK*)nag)->n))
      {
          find_ob = nag;
          break;
      }


    ObiektTok (&off, offk, &offob, object_type);
  }
  return find_ob;
}
