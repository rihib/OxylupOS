#include "common/types.h"

// 16550 UART
#define UART0 0x10000000  // QEMU
#define RHR 0b000
#define THR 0b000
#define IER 0b001
#define FCR 0b010
#define ISR 0b010
#define LCR 0b011
#define MCR 0b100
#define LSR 0b101
#define MSR 0b110
#define SPR 0b111

static inline uint8_t read_uart(phys_addr_t offset) {
  uint8_t *addr = (uint8_t *)(UART0 + offset);
  return *addr;
}

static inline void write_uart(phys_addr_t offset, uint8_t val) {
  uint8_t *addr = (uint8_t *)(UART0 + offset);
  *addr = val;
}
