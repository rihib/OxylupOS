#include "stdio.h"

#include "common/stdlib.h"
#include "common/types.h"
#include "prototypes.h"

int printf(const char *fmt, ...) {
  int count = 0;
  va_list ap;

  if (!fmt) {
    PANIC("fmt is NULL");
  }

  va_start(ap, fmt);
  const char *s;
  while (*fmt) {
    if (*fmt != '%') {
      if (putchar(*fmt) == EOF) {
        return EOF;
      }
      count++;
    } else {
      fmt++;
      switch (*fmt) {
        case '%':
          if (putchar('%') == EOF) {
            return EOF;
          }
          count++;
          break;
        case 'd': {
          char buf[12];
          itoa(va_arg(ap, int), buf, 10);
          s = buf;
          while (*s) {
            if (putchar(*s++) == EOF) {
              return EOF;
            }
            count++;
          }
          break;
        }
        case 's':
          s = va_arg(ap, const char *);
          while (*s) {
            if (putchar(*s++) == EOF) {
              return EOF;
            }
            count++;
          }
          break;
        case 'x': {
          char buf[9];
          itoa(va_arg(ap, int), buf, 16);
          s = buf;
          while (*s) {
            if (putchar(*s++) == EOF) {
              return EOF;
            }
            count++;
          }
          break;
        }
        default:
          if (putchar('%') == EOF) {
            return EOF;
          }
          count++;
          break;
      }
    }
    fmt++;
  }
  va_end(ap);

  return count;
}

int puts(const char *s) {
  if (!s) {
    s = "(null)";
  }
  printf(s);
  if (putchar('\n') == EOF) {
    return EOF;
  }
  return 0;
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
