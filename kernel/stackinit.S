.section .text.boot
.global initstack
initstack:
  .equ STACK_SIZE, 4096

  la sp, stack
  li a0, STACK_SIZE
  csrr a1, mhartid
  addi a1, a1, 1
  mul a0, a0, a1
  add sp, sp, a0
  call initregs
halt:
  j halt
