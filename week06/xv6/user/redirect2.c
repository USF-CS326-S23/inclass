// Redirect README as the input to the wc command

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int id, wid, exitcode;
  int r;
  int fd;
  char *newargv[5];

  id = fork();

  if(id == 0){
    // we are in the child

    // close stdin
    close(0);

    fd = open("README", O_RDONLY);
    if(fd < 0){
      fprintf(2, "open() failed\n");
      exit(-1);
    }      

    newargv[0] = "wc";
    newargv[1] = 0;
    r = exec("wc", newargv);
    // NOT REACHED ON SUCCESS
    fprintf(2, "exec() failed: %d\n", r);
    exit(-1);
  }else{
    wid = wait(&exitcode);
    printf("Parent: wait() return id = %d\n", wid);
    printf("Parent: exitcode = %d\n", exitcode);
  }

  exit(0);
}
