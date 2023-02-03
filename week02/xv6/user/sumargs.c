#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int sum = 0;
  int i;

  for (i = 1; i < argc; i++) {
   	sum = sum + atoi(argv[i]);
  }

  printf("%d\n", sum);

  exit(0);
}
