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

void
myfree(void *p)
{
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

  /* This code developed in class can pass the first test.
   * It assumes several things:
   * - nbytes is less than (4096 - (sizeof(struct block_hdr) + 4))
   * - it will only be called once
   */

  /* Use void * pointers for pointer arithmetic */
  void *heap_start;
  void *free_start;

  /* This will be pointers to the new used block and free block */
  struct block_hdr *used_p;
  struct block_hdr *free_p;

  /* Ask for 4096 bytes from kernel.
   * return value is a pointer to the beginning of this region.
   */
  heap_start = sbrk(BLOCK_MIN_INCR);

  /* Type cast the heap_start into a pointer to a struct block_hdr */
  used_p = (struct block_hdr *) heap_start;

  /* Set the fields of the new used block */
  used_p->used = 1;
  used_p->size = nbytes;
  strcpy(used_p->name, name);

  /* Add the used block to the block_list */
  list_push_back(&block_list, &(used_p->elem));

  /* Calculate the address of where the free block should go.
   * Use void * for pointer arithmetic.
   */
  free_start = heap_start + sizeof(struct block_hdr) + nbytes;

  /* Type cast the free_start into a pointer to a struct block_hdr */
  free_p = (struct block_hdr *) free_start;

  /* Set the fields of the new free block */
  free_p->used = 0;
  /* Calculate how much usable free space will be in the free block */
  free_p->size = BLOCK_MIN_INCR -
             (sizeof(struct block_hdr) + nbytes +
              sizeof(struct block_hdr));
  /* Set the name string of any free block to the empty string */
  free_p->name[0] = '\0';

  /* Add the free block to the block_list */
  list_push_back(&block_list, &(free_p->elem));

  /* Calculate the address of the start of usable data in the used block */
  p = heap_start + sizeof(struct block_hdr);

  return p;
}

void*
malloc_name_given(uint nbytes, const char *name)
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
  p = malloc_name_given(nbytes, "");
  return p;
}
