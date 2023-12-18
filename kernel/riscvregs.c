#include "riscvregs.h"

#include "stdio.h"
#include "common/types.h"

void set_mstatus_mpp(char mode) {
  uint64_t mstatus = read_mstatus();

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
