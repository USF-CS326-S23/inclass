// Example of fork() then exec() in child.

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int id, wid, exitcode;
  int r;
  char *newargv[5];

  id = fork();

  if(id == 0){
    // we are in the child
    newargv[0] = "ls";
    newargv[1] = 0;
    r = exec(newargv[0], newargv);
    // NOT REACHED ON SUCCESS
    fprintf(2, "exec() failed: %d\n", r);
    exit(-1);
  }else{
    // we are in the parent
    wid = wait(&exitcode);
    printf("Parent: wait() return id = %d\n", wid);
    printf("Parent: exitcode = %d\n", exitcode);
  }

  exit(0);
}
