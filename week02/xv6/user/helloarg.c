#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;

  if (argv[1][0] == '-' && argv[1][1] == 'l'
      && argv[1][2] == '\0') {
    printf("Found -l\n");
  }

  for (i = 0; i < argc; i++){
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  exit(0);
}
