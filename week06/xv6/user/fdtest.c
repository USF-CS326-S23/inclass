#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int fd1, fd2;
  int r;
  char buf[128];

  // Create foo.txt and for writing only
  fd1 = open("foo.txt", O_CREATE | O_WRONLY);
  printf("fd1 = %d\n", fd1);
  if(fd1 < 0){
    fprintf(2, "open(foo.txt) failed\n");
    exit(-1);
  }
  r = write(fd1, "foo\nbar\n", 8);
  printf("r = write() is %d\n", r);
  if(r < 0){
    fprintf(2, "write(fd1) failed\n");
    exit(-1);
  }
  close(fd1);

  // Open foo.txt for reading only
  fd2 = open("foo.txt", O_RDONLY);
  printf("fd2 = %d\n", fd2);
  if(fd2 < 0){
    fprintf(2, "open(foo.txt) failed\n");
    exit(-1);
  }
  r = read(fd2, buf, 127);
  printf("r = read() is %d\n", r);
  if(r < 0){
    fprintf(2, "read(fd2) failed\n");
    exit(-1);
  }
  buf[r] = '\0';
  printf("buf[] = %s\n", buf);
  close(fd2);

  exit(0);
}
