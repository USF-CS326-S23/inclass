#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/list.h"
#include "user/user.h"

struct list block_list_2;

long heap_start_2;

struct block_hdr {
  struct list_elem elem;
  char name[8];
  int used;
  int size;
};

void
malloc_print_2(void)
{
  struct list_elem *e;
  struct list *lp = &block_list_2;
  struct block_hdr *hp;
  char *used = "USED";
  char *free = "FREE";
  char *s;
  long offset;

   for (e = list_begin(lp); e != list_end(lp); e = list_next(e)) {
    hp = list_entry(e, struct block_hdr, elem);
    if(hp->used){
      s = used;
    }else{
      s = free;
    }
    offset = ((long) hp) - heap_start_2;
    printf("[%s] name = %s offset = %l size = %d\n",
           s, hp->name, offset, hp->size);
  }
  return;
}

int
main(int argc, char **argv)
{
  void *p;
  struct block_hdr *hp;
  struct block_hdr *fp;
  int size;
  int req;

  list_init(&block_list_2);

  req = 4096;
  p = sbrk(req);
  heap_start_2 = (long) p;
 
  size = 40;
  hp = (struct block_hdr *) p;

  hp->used = 1;
  hp->size = size;

  list_push_back(&block_list_2, &(hp->elem));

  p = ((void *) hp) + sizeof(struct block_hdr);

  fp = (struct block_hdr *) (((void *) hp) 
       + sizeof(struct block_hdr) + size);

  fp->used = 0;
  fp->size = req - (sizeof(struct block_hdr) + size
                    + sizeof(struct block_hdr));

  list_push_back(&block_list_2, &(fp->elem));

  
  malloc_print_2();

  exit(0);
}
