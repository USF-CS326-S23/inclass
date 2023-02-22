#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define BUFSIZE 512
#define NUMSIZE 6
#define NUMWIDTH (NUMSIZE + 2)

char buf[BUFSIZE];

int
readline(int fd, char *buf, int maxlen)
{
  int n;
  char c;
  int i = 0;

  while((n = read(fd, &c, 1)) > 0){
    buf[i] = c;
    if (c == '\n'){
      break;
    }
    i += 1;
    if (i >= (maxlen - 1)){
      fprintf(2, "readline() - line too long\n");
      exit(-1);
    }
  }
  if(((n == 0) && (i == 0)) || (n < 0))
    return n;
  i += 1;
  buf[i] = '\0';
  return i;
}

void int_to_str(int value, char *str) {
    int div, rem;
    int i, j = 0, len;
    int obase = 10;
    char tmp[32];
    int diff;

    len = 0;
    if(value == 0)
     tmp[len++] = '0';
    else{
      while (value != 0) {
        div = value / obase;
        rem = value % obase;
        if (rem <= 9)
          tmp[len] = '0' + rem;
        len += 1;
        value = div;
      }
    }

    diff = NUMSIZE - len;
    for (j = 0; j < diff; j++){
      str[j] = ' ';    
    }

    /* Reverse tmp string and put into result string */
    for (i = len; i > 0; i--, j++) {
        str[j] = tmp[i-1];
    }
    str[j] = ' ';
    j += 1;
    str[j] = ' ';
    j += 1;
    str[j] = '\0';
}

void
cat(int fd, int linenums)
{
  int n;
  int i = 1;
  char linenum_str[32];

  while((n = readline(fd, buf, BUFSIZE)) > 0) {
    if (linenums) {
      int_to_str(i, linenum_str);
      if(write(1, linenum_str, NUMWIDTH) != NUMWIDTH){
        fprintf(2, "cat: write error\n");
        exit(1);
      }
    }
    if(write(1, buf, n) != n){
      fprintf(2, "cat: write error\n");
      exit(1);
    }
    i += 1;
  }

  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  int fd, i = 1;
  int linenums = 0;

/*
  char buf[32];
  int_to_str(731, buf);
  printf("buf = %s\n", buf);
  exit(0);
*/

  if(argc <= 1){
    cat(0, linenums);
    exit(0);
  }

  if(argv[1][0] == '-' && argv[1][1] == 'n') {
    linenums = 1;
    i = 2;
  }

  if (linenums && (argc == 2)){
    cat(0, linenums);
    exit(0);
  }

  for(; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    cat(fd, linenums);
    close(fd);
  }
  exit(0);
}
