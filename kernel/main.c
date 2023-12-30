#include "common/types.h"
#include "proc.h"
#include "prototypes.h"
#include "riscvregs.h"
#include "stdio.h"

// TODO: Make OS 32-bit compatible
// TODO: Make comprehensive tests

struct pcb *proca;
struct pcb *procb;

void proca_func(void) {
  printf("procA\n");
  while (1) {
    sched_yield();
    putchar('A');
    for (int i = 0; i < 100000000; i++) {
      __asm__ __volatile__("nop");
    }
  }
}

void procb_func(void) {
  printf("procB\n");
  while (1) {
    sched_yield();
    putchar('B');
    for (int i = 0; i < 100000000; i++) {
      __asm__ __volatile__("nop");
    }
  }
}

static __volatile__ bool_t booted = false;

void main(void) {
  int cpuid = (int)read_tp();

  if (cpuid == 0) {
    inituart();
    if (printf("\nOxylupOS starts booting!!\n") == EOF) {
      PANIC("Cannot print");
    }

    phys_addr_t pages0 = alloc_pages(2);
    if (!pages0) {
      PANIC("Failed to allocate page");
    }
    phys_addr_t pages1 = alloc_pages(1);
    if (!pages1) {
      PANIC("Failed to allocate page");
    }
    printf("pages0 = %x\n", pages0);
    printf("pages1: %x\n", pages1);

    initidleproc();
    proca = initproc((uintptr_t)proca_func);
    procb = initproc((uintptr_t)procb_func);
    sched_yield();
    PANIC("Failed to boot");

    if (printf("Welcome to OxylupOS!!\n\n") == EOF) {
      PANIC("Cannot print");
    }
    booted = true;
  } else {
    while (!booted)
      ;
  }
}
