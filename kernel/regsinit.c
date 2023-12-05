#include "prototypes.h"
#include "riscvregs.h"
#include "types.h"

void regsinit(void) {
  int hartid = (int)read_mhartid();
  write_tp(hartid);
  set_mstatus_mpp('S');
  write_medeleg(0xffff);
  write_mideleg(0xffff);
  write_mepc((uint64_t)main);
  write_pmpaddr0(0x3fffffffffffffull);
  write_pmpcfg0(0xf);
  write_sie(read_sie() | 0b1000100010);
  write_satp(0);
  __asm__ __volatile__("mret");
}
