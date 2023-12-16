#include "prototypes.h"
#include "types.h"

void putchar(int c) {
  if (c == '\b') {
    uartputchar('\b', false);
    uartputchar(' ', false);
    uartputchar('\b', false);
  } else {
    uartputchar((uint8_t)c, false);
  }
}
