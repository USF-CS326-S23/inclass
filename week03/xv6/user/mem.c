#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int x = 3;
int y = 4;

int
foo(int d)
{
  int z;
  z = 9;

  printf("---------------------");
  printf("LOCAL DATA foo\n");
  printf("&z       = %p\n", &z);

  return z + d;
}

int
main(int argc, char **argv)
{
  int a;
  int b;
  char s[10];
  char *p;

  a = 1;
  b = 2;
  a = a + b;
  s[0] = '\0';

  p = (char *) malloc(32);
  p[0] = s[0];

  printf("---------------------");
  printf("CODE\n");
  printf("&foo()    = %p\n", foo);
  printf("&main()   = %p\n", main);
  printf("&printf() = %p\n", printf);
  printf("---------------------");
  printf("DATA\n");
  printf("&x        = %p\n", &x);
  printf("&y        = %p\n", &y);
  printf("---------------------");
  printf("LOCAL DATA main\n");
  printf("&a        = %p\n", &a);
  printf("&b        = %p\n", &b);
  printf("---------------------");
  printf("HEAP DATA\n");
  printf("p         = %p\n", p);

  a = foo(11);
  
  exit(0);
}
