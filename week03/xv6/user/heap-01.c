#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char **argv)
{
  void *h0;
  void *h1;
  void *h2;

  h0 = sbrk(1);
  h1 = sbrk(1);
  h2 = sbrk(1);

  printf("h0 = %p\n", h0);
  printf("h1 = %p\n", h1);  
  printf("h2 = %p\n", h2);

  exit(0);
}
