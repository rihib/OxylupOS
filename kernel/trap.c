#include "common/types.h"
#include "prototypes.h"
#include "riscvregs.h"
#include "stdio.h"

void inittrap(void) { write_stvec((uint64_t)trapentry); }

__attribute__((naked)) __attribute__((aligned(4))) void trapentry(void) {
  __asm__ __volatile__(
      "addi sp, sp, -8 * 31\n"
      "sd ra, 8 * 0(sp)\n"
      "sd gp, 8 * 1(sp)\n"
      "sd tp, 8 * 2(sp)\n"
      "sd t0, 8 * 3(sp)\n"
      "sd t1, 8 * 4(sp)\n"
      "sd t2, 8 * 5(sp)\n"
      "sd t3, 8 * 6(sp)\n"
      "sd t4, 8 * 7(sp)\n"
      "sd t5, 8 * 8(sp)\n"
      "sd t6, 8 * 9(sp)\n"
      "sd a0, 8 * 10(sp)\n"
      "sd a1, 8 * 11(sp)\n"
      "sd a2, 8 * 12(sp)\n"
      "sd a3, 8 * 13(sp)\n"
      "sd a4, 8 * 14(sp)\n"
      "sd a5, 8 * 15(sp)\n"
      "sd a6, 8 * 16(sp)\n"
      "sd a7, 8 * 17(sp)\n"
      "sd s0, 8 * 18(sp)\n"
      "sd s1, 8 * 19(sp)\n"
      "sd s2, 8 * 20(sp)\n"
      "sd s3, 8 * 21(sp)\n"
      "sd s4, 8 * 22(sp)\n"
      "sd s5, 8 * 23(sp)\n"
      "sd s6, 8 * 24(sp)\n"
      "sd s7, 8 * 25(sp)\n"
      "sd s8, 8 * 26(sp)\n"
      "sd s9, 8 * 27(sp)\n"
      "sd s10, 8 * 28(sp)\n"
      "sd s11, 8 * 29(sp)\n"
      "sd sp, 8 * 30(sp)\n"

      "call traphandler\n"

      "ld ra, 8 * 0(sp)\n"
      "ld gp, 8 * 1(sp)\n"
      // tp is not restored in case cpu is switched during trap handling
      "ld t0, 8 * 3(sp)\n"
      "ld t1, 8 * 4(sp)\n"
      "ld t2, 8 * 5(sp)\n"
      "ld t3, 8 * 6(sp)\n"
      "ld t4, 8 * 7(sp)\n"
      "ld t5, 8 * 8(sp)\n"
      "ld t6, 8 * 9(sp)\n"
      "ld a0, 8 * 10(sp)\n"
      "ld a1, 8 * 11(sp)\n"
      "ld a2, 8 * 12(sp)\n"
      "ld a3, 8 * 13(sp)\n"
      "ld a4, 8 * 14(sp)\n"
      "ld a5, 8 * 15(sp)\n"
      "ld a6, 8 * 16(sp)\n"
      "ld a7, 8 * 17(sp)\n"
      "ld s0, 8 * 18(sp)\n"
      "ld s1, 8 * 19(sp)\n"
      "ld s2, 8 * 20(sp)\n"
      "ld s3, 8 * 21(sp)\n"
      "ld s4, 8 * 22(sp)\n"
      "ld s5, 8 * 23(sp)\n"
      "ld s6, 8 * 24(sp)\n"
      "ld s7, 8 * 25(sp)\n"
      "ld s8, 8 * 26(sp)\n"
      "ld s9, 8 * 27(sp)\n"
      "ld s10, 8 * 28(sp)\n"
      "ld s11, 8 * 29(sp)\n"
      "ld sp, 8 * 30(sp)\n"
      "addi sp, sp, 8 * 31\n"

      "sret\n");
}

void traphandler(void) {
  uint64_t scause = read_scause();
  uint64_t stval = read_stval();
  uint64_t user_pc = read_sepc();

  PANIC("unexpected trap scause=%x, stval=%x, sepc=%x\n", scause, stval,
        user_pc);
}
