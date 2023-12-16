#include "prototypes.h"
#include "riscvregs.h"
#include "types.h"

static __volatile__ bool_t booted = false;

void main(void) {
  int cpuid = (int)read_tp();

  if (cpuid == 0) {
    uartinit();
    putchar('H');
    putchar('e');
    putchar('l');
    putchar('l');
    putchar('o');
    putchar(',');
    putchar(' ');
    putchar('w');
    putchar('o');
    putchar('r');
    putchar('l');
    putchar('d');
    putchar('!');
    putchar('?');
    putchar('\b');
    putchar('\n');
    booted = true;
  } else {
    while (!booted)
      ;
  }

  for (;;)
    ;
}
