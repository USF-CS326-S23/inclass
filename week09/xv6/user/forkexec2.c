// Example of fork() then exec() with an argument

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
    newargv[0] = "echo";
    newargv[1] = "Hello";
    newargv[2] = 0;
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
