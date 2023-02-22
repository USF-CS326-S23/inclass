#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/list.h"
#include "kernel/param.h"

/* Starter implemenation of malloc()/free() */

#define BLOCK_MIN_INCR 4096
#define BLOCK_MIN_SIZE 4

/* DO NOT CHANGE */
struct block_hdr {
  struct list_elem elem;
  char name[8];
  int used;
  int size;
};

/* These are required for your implementation */
/* DO NOT CHANGE */
struct list block_list;
int heap_initialized = 0;
long heap_start = 0;

/* Pretty print the block list */
/* DO NOT CHANGE */
void
malloc_print(void)
{
  struct list_elem *e;
  struct list *lp = &block_list;
  struct block_hdr *hp;
  char *used = "USED";
  char *free = "FREE";  
  char *s;
  char *none = "NONE";
  char *name;
  long offset;  

  if(!heap_initialized){
    fprintf(2, "malloc_print() - heap not initialized\n");
    exit(-1);
  }

  for (e = list_begin(lp); e != list_end(lp); e = list_next(e)) {
    hp = list_entry(e, struct block_hdr, elem);

    if(hp->name[0] == '\0'){
        name = none;
    }else{
        name = hp->name;
    }

    if(hp->used){
      s = used;
    }else{
      s = free;
    }
    offset = ((long) hp) - heap_start;

    printf("[%s] name = %s boff = %l bsize = %l doff = %l dsize = %d\n",
           s, name, offset, sizeof(struct block_hdr) + hp->size,
           offset + sizeof(struct block_hdr), hp->size);
  }
  return;
}

/* Print a summary of the heap allocator 
 * 
 * used_mem is the total size of all the used blocks (size field)
 * free_mem is the total size of all the free blocks (size field)
 * over_mem is the overhead from all the struct block_hdr
 *
 * u+f+o is the sum user_mem + free_mem + over_mem
 * total is the total heap size
 * 
 * u+f+o should equal total
 */
 
/* DO NOT CHANGE */
void
malloc_summary(void)
{
  struct list_elem *e;
  struct list *lp = &block_list;
  struct block_hdr *hp;
  long used_mem = 0;
  long free_mem = 0;
  long over_mem = 0; 
  long total;

  if(!heap_initialized){
    fprintf(2, "malloc_summary() - heap not initialized\n");
    exit(-1);
  }

  total = sbrksz() - heap_start;

  for (e = list_begin(lp); e != list_end(lp); e = list_next(e)) {
    hp = list_entry(e, struct block_hdr, elem);
    if(hp->used){
      used_mem += hp->size;
    }else{
      free_mem += hp->size;
    }
    over_mem += sizeof(struct block_hdr);
  }
  printf("malloc_summary():\n");
  printf("used  : %l\n", used_mem);
  printf("free  : %l\n", free_mem);
  printf("over  : %l\n", over_mem);
  printf("u+f+o : %l\n", used_mem + free_mem + over_mem);
  printf("total : %l\n", total);
}

void
free(void *p)
{
  /* PUT YOUR CODE HERE */
  /* Consider breaking out code in to separate functions. */  
  return;
}

void*
malloc_name(uint nbytes, const char *name)
{
  void *p;

  debug_print("nbytes = %d, name = %s\n", nbytes, name);
  
  if(strlen(name) > 7){
    fprintf(2, "malloc_name() - name too long\n");
    exit(-1);
  }

  if(!heap_initialized){
    /* Put heap initialization code here */

    /* Initialize the heap block list */
    list_init(&block_list);

    /* Set heap_start to be top of process memory */
    heap_start = sbrksz();

    heap_initialized = 1;
  }

  /* PUT YOUR CODE HERE */
  /* Consider breaking out code in to separate functions. */
  p = sbrk(nbytes);

  return p;
}

void*
malloc(uint nbytes)
{
  void *p;
  p = malloc_name(nbytes, "");
  return p;
}
