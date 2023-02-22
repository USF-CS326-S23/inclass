#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

void
free(void *ap)
{
  return;
}

void*
malloc(uint nbytes)
{
  void *p;

  p = sbrk(nbytes);

  return p;
}
