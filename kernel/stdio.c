#include "prototypes.h"
#include "types.h"

int puts(const char *s) {
  if (s == NULL) s = "(null)";
  while (*s)
    if (putchar(*s++) == EOF) return EOF;
  if (putchar('\n') == EOF) return EOF;
  return 0;
}

void panic(const char *s) {
  const char *pm = "PANIC: ";
  while (*pm)
    if (putchar(*pm++) == EOF) break;
  if (s == NULL) s = "(null)";
  puts(s);
  for (;;)
    ;
}

int putchar(int c) {
  if (c == '\b') {
    uartputchar('\b', false);
    uartputchar(' ', false);
    uartputchar('\b', false);
  } else {
    uartputchar((uint8_t)c, false);
  }
  return c;
  // TODO: Error handling (return EOF) when cannot write to UART and so on
}
