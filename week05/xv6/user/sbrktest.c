#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/list.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  long sz;
  //long *p;
  //long v;
  char *p;

  sz = sbrksz();

  printf("sz = %l\n", sz);

  p = (char *) sz;

  p[0] = 'a';

  //p = &sz;

  //printf("p = %p\n", p);

  //v = sz - ((long) p);

  //printf("v = %l\n", v);

  exit(0);  
}
