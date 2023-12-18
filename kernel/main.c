#include "prototypes.h"
#include "riscvregs.h"
#include "stdio.h"
#include "types.h"

static __volatile__ bool_t booted = false;

void main(void) {
  int cpuid = (int)read_tp();

  if (cpuid == 0) {
    inituart();
    if (printf("\nOxylupOS starts booting!!\n") == EOF) {
      PANIC("Cannot print");
    }
    inittrap();
    __asm__ __volatile__("unimp");
    if (printf("Welcome to OxylupOS!!\n\n") == EOF) {
      PANIC("Cannot print");
    }
    booted = true;
  } else {
    while (!booted)
      ;
  }
}
