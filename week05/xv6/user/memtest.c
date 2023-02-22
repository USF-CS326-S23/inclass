#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/list.h"
#include "user/user.h"

extern long heap_start;

void
mem_scribble(char *buf, long count, char value)
{
  int i;

  for(i = 0; i < count; i++){
    buf[i] = value;
  }
}

int
mem_scribble_check(char *buf, long count, char value)
{
  int valid = 1;
  int i;
  
  for(i = 0; i < count; i++){
    if(buf[i] != value){
      valid = 0;
      break;
    }
  }
  return valid;
}


#define MAX_PTRS 32

/* This stuct is used to keep track of allocations */
struct memptrs_st {
    void *ptr;
    long size;
    int used;
};


/* Check that all used blocks have the scribble values.
 * Check that the heap size is less then given size.
 */
int
mem_check(struct memptrs_st memptrs[], int count, long size)
{
  int valid = 1;
  int i;
  long heap_size;
  
  for(i = 0; i < count; i++){
    if(memptrs[i].used == 1){
      valid = mem_scribble_check(memptrs[i].ptr, memptrs[i].size, 0xAA);
    }
    if(valid == 0){
      printf("mem_check() failed at %p, used = %d\n",
             memptrs[i].ptr, memptrs[i].used);
      exit(-1);
    }
  }

  heap_size = sbrksz() - heap_start;
  if(heap_size > size){
    printf("mem_check() failed actual heap size %l > %l\n",
           heap_size, size);
    exit(-1);
  }

  printf("mem_check() passed with heap less than %d\n", size);
  
  return valid;
}

/*
 * memrefs - a mini langauge to describe memory requests
 *
 * (m)alloc
 * a <index> <size> <name>
 * (f)ree
 * f <index>
 * (p)rint block list
 * (s)ummary of block list 
 * (c)heck block list
 */
void
mem_refs(int argc, char **argv)
{
  int i = 1;
  int index;
  int size = 0;
  char *name;
  struct memptrs_st memptrs[MAX_PTRS];

  debug_print("argc = %d\n", argc); 

  while(i < argc){
    if(strcmp(argv[i], "m") == 0){
      debug_print("argv[%d] = %s\n", i, argv[i]); 
      /* (m)alloc */
      if((argc - i) < 4){
        fprintf(2, "mem_refs() - Not enough arguments for (m)alloc\n");
        exit(-1);
      }
      index = atoi(argv[i + 1]);
      size = atoi(argv[i + 2]);
      name = argv[i + 3];
      debug_print("cmd = %s, index = %d, size = %d, name = %s\n",
                  argv[i], index, size, name);
      memptrs[index].size = size;
      memptrs[index].ptr = (void *) malloc_name(size, name);
      memptrs[index].used = 1;
      mem_scribble(memptrs[index].ptr, size, 0xAA);
      i += 4;
    }else if(strcmp(argv[i], "f") == 0){
      /* (f)ree */
      if((argc - i) < 2){
        fprintf(2, "memrefs() - Not enough arguments for (f)ree\n");
        exit(-1);
      }
      index = atoi(argv[i + 1]);
      size = memptrs[index].size;
      mem_scribble(memptrs[index].ptr, size, 0x55);
      memptrs[index].used = 0;
      myfree(memptrs[index].ptr);
      i += 2;
      debug_print("cmd = %s, index = %d\n",
                  argv[i], index);
    }else if(strcmp(argv[i], "p") == 0){
      /* (p)rint */
      malloc_print();
      i += 1;
    }else if(strcmp(argv[i], "s") == 0){
      /* (s)ummary */
      malloc_summary();
      i += 1;
    }else if(strcmp(argv[i], "c") == 0){
      /* (c)heck */
      if((argc - i) < 2){
        fprintf(2, "mem_refs() - Not enough arguments for (c)heck\n");
        exit(-1);
      }
      size = atoi(argv[i + 1]);
      mem_check(memptrs, index, size);
      i += 2;
    }else{
      fprintf(2, "memrefs() - command %s not recognized\n",
              argv[i]);
      exit(-1);
    }
  }
}

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "usage: memtest <commands>\n");
    exit(-1);
  }

  debug_print("argc = %d\n", argc);
  mem_refs(argc, argv);

  exit(0);
}
