#include "uart.h"

#include "common/types.h"

void inituart(void) {
  write_uart(IER, 0b00000000);
  write_uart(LCR, 0b10000000);
  write_uart(0, 0b00000011);
  write_uart(1, 0b00000000);
  write_uart(LCR, 0b00000011);
  write_uart(FCR, 0b00000111);
  write_uart(IER, 0b00000011);
}

void uartputchar(uint8_t c, bool_t can_interrupt) {
  if (!can_interrupt) {
    while ((read_uart(LSR) & 0b00100000) == 0) {
      ;
    }
    write_uart(THR, c);
    return;
  }
  // TODO: implement interrupt-driven uartputchar
  return;
}
