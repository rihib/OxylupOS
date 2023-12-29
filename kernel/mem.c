#include "mem.h"

#include "common/stdlib.h"
#include "common/types.h"
#include "stdio.h"

extern char __kernel_end[];

phys_addr_t alloc_pages(int n) {
  static phys_addr_t next_freepage = (phys_addr_t)__kernel_end;
  phys_addr_t ret = next_freepage;
  next_freepage += (phys_addr_t)(n * PAGESIZE);
  if (next_freepage > (phys_addr_t)PMEMEND) {
    PANIC("Out of memory\n");
  }
  memset((void *)ret, 0, n * PAGESIZE);
  return ret;
}
