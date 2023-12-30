#include "common/types.h"
#include "mem.h"
#include "proc.h"
#include "prototypes.h"
#include "riscvregs.h"

extern struct pcb proctable[NPROC];
extern struct pcb *currproc;
extern struct pcb *idleproc;

void sched_yield(void) {
  struct pcb *prev = NULL;
  struct pcb *next = NULL;

  // Find next runnable process except for idleproc, and switch to it
  for (int i = 0; i < NPROC; i++) {
    int n = (currproc->pid + i) % NPROC;
    if (proctable[n].pid != IDLEPID && proctable[n].state == RUNNABLE) {
      next = &proctable[n];
      break;
    }
  }

  // If current process is the only runnable process, do nothing
  if (next == currproc) {
    return;
  }

  // If there is no runnable process except for idleproc, switch to idleproc
  if (!next) {
    next = idleproc;
  }

  sfence_vma();
  write_satp(SATP_MODE_SV39 | (uint64_t)next->pagetable / PAGESIZE);
  sfence_vma();

  prev = currproc;
  currproc = next;
  switch_context(&prev->sp, &next->sp);
}
