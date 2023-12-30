#include "mem.h"

#include "common/stdlib.h"
#include "common/types.h"
#include "prototypes.h"
#include "riscvregs.h"
#include "stdio.h"

extern char __ram_start[], __ram_end[];

void map_kernelpage(pagetable_t pagetable) {
  for (phys_addr_t pa = (phys_addr_t)__kernel_base; pa < (phys_addr_t)__ram_end;
       pa += PAGESIZE) {
    map_page(pagetable, pa, pa, PTE_R | PTE_W | PTE_X);
  }
}

void map_page(pagetable_t pagetable, uintptr_t va, phys_addr_t pa,
              uint64_t pte_bits) {
  if (va >= (1LL << (9 + 9 + 9 + 12 - 1))) {
    PANIC("Given virtual address is too large");
  }
  if (pa >= (1LL << (26 + 9 + 9 + 12 - 1))) {
    PANIC("Given physical address is too large");
  }
  if (!IS_ALIGNED(va, PAGESIZE)) {
    PANIC("Given virtual address is not aligned");
  }
  if (!IS_ALIGNED(pa, PAGESIZE)) {
    PANIC("Given physical address is not aligned");
  }

  uint64_t *pte;
  // VPN2, VPN1
  for (int level = 2; level > 0; level--) {
    uint64_t index = (va >> (9 * level + 12)) & 0b111111111;
    pte = &pagetable[index];
    if (*pte & PTE_V) {
      pagetable = (pagetable_t)(((*pte >> 10) * PAGESIZE));
    } else {
      pagetable = (pagetable_t)alloc_pages(1);
      if (!pagetable) {
        PANIC("Failed to allocate page");
      }
      memset((void *)pagetable, 0, PAGESIZE);
      *pte = (((uint64_t)pagetable / PAGESIZE) << 10) | PTE_V;
    }
  }
  // VPN0
  pte = &pagetable[(va >> 12) & 0b111111111];
  if (*pte & PTE_V) {
    PANIC("Attempted to remap an already mapped page table entry");
  }
  *pte = (((uint64_t)pa / PAGESIZE) << 10) | pte_bits | PTE_V;
}

phys_addr_t alloc_pages(int n) {
  static phys_addr_t next_freepage = (phys_addr_t)__ram_start;
  if (next_freepage > (phys_addr_t)__ram_end) {
    return (phys_addr_t)NULL;
  }
  phys_addr_t ret = next_freepage;
  next_freepage += (phys_addr_t)(n * PAGESIZE);
  memset((void *)ret, 0, n * PAGESIZE);
  return ret;
}
