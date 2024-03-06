#include "proc.h"

#include "common/stdlib.h"
#include "common/types.h"
#include "stdio.h"

// TODO: Multicore support. Maybe need to save cpu state?

struct pcb proctable[NPROC];
struct pcb *currproc;
struct pcb *idleproc;

void initidleproc(void) {
  idleproc = initproc((uintptr_t)NULL);
  idleproc->pid = IDLEPID;
  currproc = idleproc;
}

struct pcb *initproc(uintptr_t pc) {
  // Find unused process and return it after initializing
  struct pcb *proc = NULL;
  for (int i = 0; i < NPROC; i++) {
    if (proctable[i].state == UNUSED) {
      proc = &proctable[i];
      uintptr_t *sp = (uintptr_t *)&proc->kstack[sizeof(proc->kstack)];
      memset(proc->kstack, 0, sizeof(proc->kstack));
      proc->pid = i + 1;
      proc->state = RUNNABLE;
      proc->sp = (uintptr_t)sp;
      proc->kstack[sizeof(proc->kstack)] = pc;
      return proc;
    }
  }
  PANIC("Cannot create new process due to maximum number of processes");
}

__attribute__((naked)) void switch_context(uintptr_t *prev_context,
                                           uintptr_t *next_context) {
  __asm__ __volatile__(
      // Save current context
      "addi sp, sp, -13 * 4\n"
      "sw ra, 0 * 4(sp)\n"
      "sw s0, 1 * 4(sp)\n"
      "sw s1, 2 * 4(sp)\n"
      "sw s2, 3 * 4(sp)\n"
      "sw s3, 4 * 4(sp)\n"
      "sw s4, 5 * 4(sp)\n"
      "sw s5, 6 * 4(sp)\n"
      "sw s6, 7 * 4(sp)\n"
      "sw s7, 8 * 4(sp)\n"
      "sw s8, 9 * 4(sp)\n"
      "sw s9, 10 * 4(sp)\n"
      "sw s10, 11 * 4(sp)\n"
      "sw s11, 12 * 4(sp)\n"
      "sw sp, (a0)\n"
      // Restore next process context
      "lw sp, (a1)\n"
      "lw ra, 0 * 4(sp)\n"
      "lw s0, 1 * 4(sp)\n"
      "lw s1, 2 * 4(sp)\n"
      "lw s2, 3 * 4(sp)\n"
      "lw s3, 4 * 4(sp)\n"
      "lw s4, 5 * 4(sp)\n"
      "lw s5, 6 * 4(sp)\n"
      "lw s6, 7 * 4(sp)\n"
      "lw s7, 8 * 4(sp)\n"
      "lw s8, 9 * 4(sp)\n"
      "lw s9, 10 * 4(sp)\n"
      "lw s10, 11 * 4(sp)\n"
      "lw s11, 12 * 4(sp)\n"
      "addi sp, sp, 13 * 4\n"
      "ret\n");
}
