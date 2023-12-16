#include "prototypes.h"
#include "riscvregs.h"
#include "types.h"

static __volatile__ bool_t booted = false;

void main(void) {
  int cpuid = (int)read_tp();

  if (cpuid == 0) {
    uartinit();
    if (putchar('\n') == EOF) panic("putchar() failed at kernel/main():12");
    if (puts("bonsaiOS starts booting!!") == EOF)
      panic("puts() failed at kernel/main():13");
    if (puts("Welcome to bonsaiOS!!") == EOF)
      panic("puts() failed at kernel/main():15");
    if (putchar('\n') == EOF) panic("putchar() failed at kernel/main():17");
    booted = true;
  } else {
    while (!booted)
      ;
  }

  for (;;)
    ;
}
