// Redirect stdin for the child to be the read end of the pipe.
// The parent writes data to the child (wc) using the write end
// of the pipe.

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
  int pfds[2];

  pipe(pfds);
  
  id = fork();

  if(id == 0){
    // we are in the child

    // close stdin
    close(0);
    dup(pfds[0]);
    close(pfds[0]);
    close(pfds[1]);

    newargv[0] = "wc";
    newargv[1] = 0;
    r = exec("wc", newargv);
    // NOT REACHED ON SUCCESS
    fprintf(2, "exec() failed: %d\n", r);
    exit(-1);
  }else{
    close(pfds[0]);
    write(pfds[1], "Foo\nBar\n", 8);
    close(pfds[1]);     
    wid = wait(&exitcode);
    printf("Parent: wait() return id = %d\n", wid);
    printf("Parent: exitcode = %d\n", exitcode);
  }

  exit(0);
}
