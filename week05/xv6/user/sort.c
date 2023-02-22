#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/list.h"
#include "user/user.h"

#define STR_LEN 128

struct line {
  struct list_elem elem;
  char value[STR_LEN];
};

void
lines_list_print(struct list *lp)
{
  struct list_elem *e;

  for (e = list_begin(lp); e != list_end(lp); e = list_next(e)){
    struct line *lp = list_entry(e, struct line, elem);
    printf("%s", lp->value);
  }
  return;
}

bool
lines_list_less(const struct list_elem *a, const struct list_elem *b, void *aux)
{
  struct line *ap;
  struct line *bp;

  ap = list_entry(a, struct line, elem);
  bp = list_entry(b, struct line, elem);  
  
  return (strcmp(ap->value, bp->value) < 0);
}

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

void
sort(int fd)
{
  int n;
  struct list lines;
  struct line *lp;
  char buf[STR_LEN];

  list_init(&lines);

  while((n = readline(fd, buf, STR_LEN)) > 0){
    //printf("buf = %d", buf);
    lp = malloc(sizeof(struct line));
    if (lp == 0){
      printf("sort() - malloc() failed\n");
      exit(-1);
    }
    strcpy(lp->value, buf);
    list_push_back(&lines, &lp->elem);
  } 

  list_sort(&lines, lines_list_less, (void *) 0);
  lines_list_print(&lines);
}

int
main(int argc, char *argv[])
{
  int fd;

  if(argc <= 1){
    sort(0);
    exit(0);
  }

  if((fd = open(argv[1], 0)) < 0){
    fprintf(2, "sort: cannot open %s\n", argv[1]);
    exit(1);
  }
  sort(fd);
  exit(0);
}
