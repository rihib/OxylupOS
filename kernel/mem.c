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

void map_page_sv32(pagetable_t pt1, phys_addr_t pa, uintptr_t va,
                   uint32_t bits) {
  if (pa >= (1 << 33)) {
    PANIC("Given physical address is too large");
  }
  if (va >= (1 << 31)) {
    PANIC("Given virtual address is too large");
  }
  if (!IS_ALIGNED(pa, PAGESIZE)) {
    PANIC("Given physical address is not page-aligned");
  }
  if (!IS_ALIGNED(va, PAGESIZE)) {
    PANIC("Given virtual address is not page-aligned");
  }

  uint16_t vpn1 = (va >> 22) & 0b1111111111;
  if ((pt1[vpn1] & PTE_V) == 0) {
    phys_addr_t pt0_base = alloc_pages(1);
    pt1[vpn1] = ((pt0_base / PAGESIZE) << 10) | PTE_V;
  }

  // If the `PTE_V` of `pt1[vpn1]` is already valid,
  // we use the existing value to get the pointer to `pt0`.
  // Therefore, we cannot simply `pagetable_t pt0 = pt0_base` here.
  pagetable_t pt0 = (pagetable_t)((pt1[vpn1] >> 10) * PAGESIZE);
  uint16_t vpn0 = (va >> 12) & 0b1111111111;
  // By performing a bitwise OR with `PTE_V` at the end,
  // we ensure that `PTE_V` is activated.
  // This prevents `PTE_V` from being accidentally deactivated by `bits`.
  pt0[vpn0] = ((pa / PAGESIZE) << 10) | bits | PTE_V;
}
