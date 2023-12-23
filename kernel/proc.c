#include "proc.h"

#include "common/stdlib.h"
#include "common/types.h"
#include "stdio.h"

// TODO: マルチコア対応

struct pcb procs[NPROC_LIMIT];

struct pcb *initproc(uintptr_t pc) {
  struct pcb *proc = NULL;
  int i;
  for (i = 0; i < NPROC_LIMIT; i++) {
    if (procs[i].state == UNUSED) {
      proc = &procs[i];
      break;
    }
  }
  if (!proc) {
    PANIC("Cannot create new process due to maximum number of processes");
  }

  proc->pid = i + 1;
  proc->state = RUNNABLE;

  uintptr_t *sp = (uintptr_t *)&proc->kstack[12];
  proc->sp = (uintptr_t)sp;

  memset(proc->kstack, 0, sizeof(proc->kstack));
  proc->kstack[12] = pc;

  return proc;
}

__attribute__((naked)) void switch_context(uintptr_t *prev_context,
                                           uintptr_t *next_context) {
  __asm__ __volatile__(
      "addi sp, sp, -13 * 8\n"
      "sd ra, 0 * 8(sp)\n"
      "sd s0, 1 * 8(sp)\n"
      "sd s1, 2 * 8(sp)\n"
      "sd s2, 3 * 8(sp)\n"
      "sd s3, 4 * 8(sp)\n"
      "sd s4, 5 * 8(sp)\n"
      "sd s5, 6 * 8(sp)\n"
      "sd s6, 7 * 8(sp)\n"
      "sd s7, 8 * 8(sp)\n"
      "sd s8, 9 * 8(sp)\n"
      "sd s9, 10 * 8(sp)\n"
      "sd s10, 11 * 8(sp)\n"
      "sd s11, 12 * 8(sp)\n"
      "sd sp, (a0)\n"
      "ld sp, (a1)\n"
      "ld ra, 0 * 8(sp)\n"
      "ld s0, 1 * 8(sp)\n"
      "ld s1, 2 * 8(sp)\n"
      "ld s2, 3 * 8(sp)\n"
      "ld s3, 4 * 8(sp)\n"
      "ld s4, 5 * 8(sp)\n"
      "ld s5, 6 * 8(sp)\n"
      "ld s6, 7 * 8(sp)\n"
      "ld s7, 8 * 8(sp)\n"
      "ld s8, 9 * 8(sp)\n"
      "ld s9, 10 * 8(sp)\n"
      "ld s10, 11 * 8(sp)\n"
      "ld s11, 12 * 8(sp)\n"
      "addi sp, sp, 13 * 8\n"
      "ret\n");
}
