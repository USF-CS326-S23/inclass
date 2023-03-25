// Example of the parent forking two processes

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int id, wid, exitcode;

  id = fork();

  if(id == 0){
    printf("Child 1, PID = %d\n", getpid());
    // Force the second child to exit first
    sleep(10);
    exit(1);
  }

  id = fork();

  if(id == 0){
    printf("Child 2, PID = %d\n", getpid());
    exit(2);
  }

  wid = wait(&exitcode);
  printf("Parent: wait() wid = %d, exitcode = %d\n", wid, exitcode);
  wid = wait(&exitcode);
  printf("Parent: wait() wid = %d, exitcode = %d\n", wid, exitcode);

  exit(0);
}
