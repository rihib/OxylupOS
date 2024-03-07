#include "mem.h"

#include "common/stdlib.h"
#include "common/types.h"
#include "stdio.h"

extern char __kernel_end[];
static phys_addr_t next_freepage;

void init_next_freepage(void) { next_freepage = (phys_addr_t)__kernel_end; }

phys_addr_t alloc_pages(int n) {
  phys_addr_t ret = next_freepage;
  next_freepage += (phys_addr_t)(n * PAGESIZE);
  if (next_freepage > (phys_addr_t)PMEMEND) {
    PANIC("Out of memory\n");
  }
  memset((void *)ret, 0, n * PAGESIZE);
  return ret;
}

void map_page(pagetable_t pagetable, phys_addr_t pa, uintptr_t va,
              pagetable_t pte_bits) {
  if (pa >= (1 << (12 + 10 + 12 - 1))) {
    PANIC("Given physical address is too large");
  }
  if (va >= (1 << (10 + 10 + 12 - 1))) {
    PANIC("Given virtual address is too large");
  }
  if (!IS_ALIGNED(pa, PAGESIZE)) {
    PANIC("Given physical address is not page-aligned");
  }
  if (!IS_ALIGNED(va, PAGESIZE)) {
    PANIC("Given virtual address is not page-aligned");
  }
}
