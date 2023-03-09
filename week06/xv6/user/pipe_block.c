// Create a pipe and send data from child to parent via pipe
// This shows how parent will block if the write end of the pipe
// is not closed.

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int id, wid, exitcode;
  int r;
  char buf[32];
  int pfds[2];

  pipe(pfds);

  id = fork();

  if(id == 0){
    // child will write to pipe
    close(pfds[0]);
    write(pfds[1], "Hello", 5);
    close(pfds[1]);
    exit(0);
  }else{
    // parent will read from pipe
    // close(pfds[1]);

    r = read(pfds[0], buf, 31);
    buf[r] = '\0';
    printf("From child: %s\n", buf);    

    r = read(pfds[0], buf, 31);
    if(r >= 0){
      buf[r] = '\0';
      printf("From child: %s\n", buf);
    }else{
      printf("read() = %d\n", r);
    }
    close(pfds[0]);

    wid = wait(&exitcode);
    printf("Parent: wait() return id = %d\n", wid);
    printf("Parent: exitcode = %d\n", exitcode);
  }

  exit(0);
}
