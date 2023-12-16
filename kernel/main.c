#include "riscvregs.h"
#include "types.h"

static __volatile__ bool_t booted = false;

void main(void) {
  int cpuid = (int)read_tp();

  if (cpuid == 0) {
    booted = true;
  } else {
    while (!booted)
      ;
  }

  for (;;)
    ;
}
