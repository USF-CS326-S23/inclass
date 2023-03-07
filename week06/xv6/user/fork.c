#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int id, wid, exitcode;
  int x = 3;

  // fork() clones this process, a complete copy
  // returns 0 in the child
  // returns the pid of the child in the parent
  // no gaurantees on order of execution of the parent and child
  id = fork();

  if(id == 0){
    // we are in the child
    printf("Child: id = %d\n", id);
    printf("Child: getpid() = %d\n", getpid());
    printf("Child: x = %d\n", x);
    x = 99;
    printf("Child: x = %d\n", x);
    printf("Child: &x = %p\n", &x);
    exit(77);
  }else{
    // we are in the parent
    printf("Parent: id = %d\n", id);
    printf("Parent: getpid() = %d\n", getpid());
    printf("Parent: wait() for the child to exit\n");
    wid = wait(&exitcode);
    printf("Parent: wait() return id = %d\n", wid);
    printf("Parent: exitcode = %d\n", exitcode);
    printf("Parent: x = %d\n", x);
    printf("Patent: &x = %p\n", &x);
  }

  exit(0);
}
