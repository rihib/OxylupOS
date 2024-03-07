#include "riscvregs.h"

#include "common/types.h"
#include "prototypes.h"
#include "stdio.h"

void initregs(void) {
  int hartid = (int)read_mhartid();
  write_tp(hartid);
  set_mstatus_mpp('S');
  write_medeleg(0xffff);
  write_mideleg(0xffff);
  write_mepc((reg_t)main);
  write_pmpaddr0(0xffffffff);
  write_pmpcfg0(0xf);
  write_sie(read_sie() | 0b1000100010);
  write_satp(0);
  __asm__ __volatile__("mret");
}

void set_mstatus_mpp(char mode) {
  reg_t mstatus = read_mstatus();

  if (mode == 'M' || mode == 'S' || mode == 'U') {
    mstatus &= ~0b1100000000000;
    if (mode == 'M') {
      mstatus |= 0b1100000000000;
    }
    if (mode == 'S') {
      mstatus |= 0b0100000000000;
    }
    if (mode == 'U') {
      mstatus |= 0b0000000000000;
    }
    write_mstatus(mstatus);
  } else {
    PANIC("Invalid mode");
  }
}
