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
      // Restore next process context
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
