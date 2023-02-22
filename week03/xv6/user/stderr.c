#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{

  printf("This is sent to stdin\n");
  fprintf(2, "This is sent to stderr\n");

  exit(0);
}
