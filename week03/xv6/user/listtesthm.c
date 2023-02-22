#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/list.h"
#include "user/user.h"

#define STR_LEN 128

struct pair {
  struct list_elem elem;
  char name[STR_LEN];
  char value[STR_LEN];
};

void
pair_list_print(struct list *lp)
{
  struct list_elem *e;

  for (e = list_begin(lp); e != list_end(lp); e = list_next(e)) {
    struct pair *p = list_entry(e, struct pair, elem);
    printf("[%s, %s]\n", p->name, p->value);
  }
  return;
}

bool
pair_list_less(const struct list_elem *a, const struct list_elem *b, void *aux)
{
  struct pair *ap;
  struct pair *bp;

  ap = list_entry(a, struct pair, elem);
  bp = list_entry(b, struct pair, elem);  
  
  return (strcmp(ap->name, bp->name) < 0);
}

struct pair *
pair_list_add(struct list *lp, char *name, char *value)
{
  struct pair *p;

  p = (struct pair *) malloc(sizeof(struct pair));
  if (p == 0) {
    fprintf(2, "pair_list_add(): malloc() failed\n");
    exit(-1);
  }

  strcpy(p->name, name);
  strcpy(p->value, value);
  list_push_back(lp, &p->elem);

  return p;
}

void
pair_list_free(struct list *lp)
{
  struct list_elem *e;

  for (e = list_begin(lp); e != list_end(lp); e = list_next(e)) {
    struct pair *p = list_entry(e, struct pair, elem);
    list_remove(e);
    free(p);
  }
  return;
}

int
main(int argc, char *argv[])
{
  struct list dmap;

  list_init(&dmap);

  pair_list_add(&dmap, "google.com", "142.251.46.174");
  pair_list_add(&dmap, "usfca.edu", "23.185.0.2");
  pair_list_add(&dmap, "mit.edu", "104.90.21.210");
  pair_list_add(&dmap, "openai.com", "13.107.238.57");

  pair_list_print(&dmap);

  /* Sort list */
  list_sort(&dmap, pair_list_less, (void *) 0);
  printf("Sorted:\n");
  pair_list_print(&dmap);

  pair_list_free(&dmap);
  
  exit(0);
}
