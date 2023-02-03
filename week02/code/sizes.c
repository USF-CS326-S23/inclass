#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("sizeof(char) = %d\n", sizeof(char));
  printf("sizeof(int) = %d\n", sizeof(int));
  printf("sizeof(long) = %d\n", sizeof(long));  
  printf("sizeof(float) = %d\n", sizeof(float));
  printf("sizeof(double) = %d\n", sizeof(double));
  printf("sizeof(char *) = %d\n", sizeof(char *));
  printf("sizeof(int *) = %d\n", sizeof(int *));
  exit(0);
}
