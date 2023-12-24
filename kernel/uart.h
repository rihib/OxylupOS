#include "common/types.h"

// 16550 UART
#define UART0 0x10000000LL  // QEMU
#define RHR 0b000LL
#define THR 0b000LL
#define IER 0b001LL
#define FCR 0b010LL
#define ISR 0b010LL
#define LCR 0b011LL
#define MCR 0b100LL
#define LSR 0b101LL
#define MSR 0b110LL
#define SPR 0b111LL

static inline uint8_t read_uart(uint64_t offset) {
  uint8_t *addr = (uint8_t *)(UART0 + offset);
  return *addr;
}

static inline void write_uart(uint64_t offset, uint8_t val) {
  uint8_t *addr = (uint8_t *)(UART0 + offset);
  *addr = val;
}
