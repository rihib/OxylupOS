#include "common/types.h"
#include "prototypes.h"
#include "riscvregs.h"
#include "stdio.h"

void inittrap(void) { write_stvec((reg_t)trapentry); }

__attribute__((naked)) __attribute__((aligned(4))) void trapentry(void) {
  __asm__ __volatile__(
      // Save current context before trap handling
      "addi sp, sp, -4 * 31\n"
      "sw ra, 4 * 0(sp)\n"
      "sw gp, 4 * 1(sp)\n"
      "sw tp, 4 * 2(sp)\n"
      "sw t0, 4 * 3(sp)\n"
      "sw t1, 4 * 4(sp)\n"
      "sw t2, 4 * 5(sp)\n"
      "sw t3, 4 * 6(sp)\n"
      "sw t4, 4 * 7(sp)\n"
      "sw t5, 4 * 8(sp)\n"
      "sw t6, 4 * 9(sp)\n"
      "sw a0, 4 * 10(sp)\n"
      "sw a1, 4 * 11(sp)\n"
      "sw a2, 4 * 12(sp)\n"
      "sw a3, 4 * 13(sp)\n"
      "sw a4, 4 * 14(sp)\n"
      "sw a5, 4 * 15(sp)\n"
      "sw a6, 4 * 16(sp)\n"
      "sw a7, 4 * 17(sp)\n"
      "sw s0, 4 * 18(sp)\n"
      "sw s1, 4 * 19(sp)\n"
      "sw s2, 4 * 20(sp)\n"
      "sw s3, 4 * 21(sp)\n"
      "sw s4, 4 * 22(sp)\n"
      "sw s5, 4 * 23(sp)\n"
      "sw s6, 4 * 24(sp)\n"
      "sw s7, 4 * 25(sp)\n"
      "sw s8, 4 * 26(sp)\n"
      "sw s9, 4 * 27(sp)\n"
      "sw s10, 4 * 28(sp)\n"
      "sw s11, 4 * 29(sp)\n"
      "sw sp, 4 * 30(sp)\n"

      "call traphandler\n"

      // Restore current context
      "lw ra, 4 * 0(sp)\n"
      "lw gp, 4 * 1(sp)\n"
      // tp is not restored in case cpu is switched during trap handling
      "lw t0, 4 * 3(sp)\n"
      "lw t1, 4 * 4(sp)\n"
      "lw t2, 4 * 5(sp)\n"
      "lw t3, 4 * 6(sp)\n"
      "lw t4, 4 * 7(sp)\n"
      "lw t5, 4 * 8(sp)\n"
      "lw t6, 4 * 9(sp)\n"
      "lw a0, 4 * 10(sp)\n"
      "lw a1, 4 * 11(sp)\n"
      "lw a2, 4 * 12(sp)\n"
      "lw a3, 4 * 13(sp)\n"
      "lw a4, 4 * 14(sp)\n"
      "lw a5, 4 * 15(sp)\n"
      "lw a6, 4 * 16(sp)\n"
      "lw a7, 4 * 17(sp)\n"
      "lw s0, 4 * 18(sp)\n"
      "lw s1, 4 * 19(sp)\n"
      "lw s2, 4 * 20(sp)\n"
      "lw s3, 4 * 21(sp)\n"
      "lw s4, 4 * 22(sp)\n"
      "lw s5, 4 * 23(sp)\n"
      "lw s6, 4 * 24(sp)\n"
      "lw s7, 4 * 25(sp)\n"
      "lw s8, 4 * 26(sp)\n"
      "lw s9, 4 * 27(sp)\n"
      "lw s10, 4 * 28(sp)\n"
      "lw s11, 4 * 29(sp)\n"
      "lw sp, 4 * 30(sp)\n"
      "addi sp, sp, 4 * 31\n"

      "sret\n");
}

void traphandler(void) {
  reg_t scause = read_scause();
  reg_t stval = read_stval();
  reg_t user_pc = read_sepc();

  PANIC("unexpected trap scause=%x, stval=%x, sepc=%x\n", scause, stval,
        user_pc);
}
