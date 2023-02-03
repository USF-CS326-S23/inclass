#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
countc(int fd)
{
  int rv;
  char c;
  int count = 0;
  
  while((rv = read(fd, &c, 1)) > 0){
    count += 1;
  }

  return count;
}

int
main(int argc, char *argv[])
{
  int fd;
  int count = 0;

  if (argc == 1) {
    count = countc(0);
  }else{
    fd = open(argv[1], 0);
    if (fd < 0){
      fprintf(2, "countc: open failed for %s\n", argv[1]);
      exit(-1);
    }
    count = countc(fd);
    close(fd);
  }

  printf("%d\n", count);
  exit(0);
}
