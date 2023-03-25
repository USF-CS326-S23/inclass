#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

void
wc(int fd, char *name, int linesonly)
{
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf("wc: read error\n");
    exit(1);
  }
  if(linesonly)
    printf("%d %s\n", l, name);
  else
    printf("%d %d %d %s\n", l, w, c, name);
}

int
main(int argc, char *argv[])
{
  int fd, i = 1;
  int linesonly = 0;
  

  if(argc <= 1){
    wc(0, "", linesonly);
    exit(0);
  }

  if(argv[1][0] == '-' && argv[1][1] == 'l') {
    linesonly = 1;
    i = 2;
  }

  if (linesonly && (argc == 2)){
    wc(0, "", linesonly);
    exit(0);    
  }

  for(; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }
    wc(fd, argv[i], linesonly);
    close(fd);
  }
  exit(0);
}
