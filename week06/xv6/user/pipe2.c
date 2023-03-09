// Create a pipe and send data from child to parent via the pipe

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int id;
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
  }

  id = fork();

  if(id == 0){
    close(pfds[1]);
    r = read(pfds[0], buf, 31);
    buf[r] = '\0';
    printf("From child: %s\n", buf);    
    close(pfds[0]);
    exit(0);
  }

  // Close both ends of pipe in parent
  close(pfds[0]);
  close(pfds[1]);

  wait(0);
  wait(0);

  return 0;
}
