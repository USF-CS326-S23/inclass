// 

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
  char *str;
  int count;
  int len;


  if(argc != 3){
    fprintf(2, "usage: pipesend <str> <count>\n");
    exit(-1);
  }

  str = argv[1];
  count = atoi(argv[2]);

  pipe(pfds);

  id = fork();

  if(id == 0){
    // child will write to pipe
    close(pfds[0]);

    len = strlen(str);
    for(int i = 0; i < count; i++){
      write(pfds[1], str, len);
    }
    close(pfds[1]);
    exit(0);
  }

  id = fork();

  if(id == 0){
    close(pfds[1]);

    while(1){
      r = read(pfds[0], buf, 31);
      printf("read() r = %d\n", r);
      if(r < 0){
        fprintf(2, "read() failed\n");
        exit(-1);
      }else if(r == 0){
        break;
      }
      buf[r] = '\0';
      printf("%s", buf);    
    }
  
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
