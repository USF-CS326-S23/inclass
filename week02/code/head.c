#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

void
head(int fd)
{
  int rv;
  int count = 0;
  
  while((rv = readline(fd, buf, 511)) > 0){
    printf("%s", buf);
    count += 1;
    if (count >= 10)
      break;
  }
}

int
main(int argc, char *argv[])
{
  int fd;

  if (argc == 1) {
    head(0);
  }else{
    fd = open(argv[1], 0);
    if (fd < 0){
      fprintf(2, "head: open failed for %s\n", argv[1]);
      exit(-1);
    }
    head(fd);
    close(fd);
  }

  exit(0);
}
