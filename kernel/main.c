#include "prototypes.h"
#include "riscvregs.h"
#include "stdio.h"
#include "types.h"

static __volatile__ bool_t booted = false;

void main(void) {
  int cpuid = (int)read_tp();

  if (cpuid == 0) {
    uartinit();
    if (printf("\nbonsaiOS starts booting!!\n") == EOF) {
      PANIC("Cannot print");
    }
    if (printf("Welcome to bonsaiOS!!\n\n") == EOF) {
      PANIC("Cannot print");
    }
    booted = true;
  } else {
    while (!booted)
      ;
  }

  PANIC("SUCCESS!!");
}
