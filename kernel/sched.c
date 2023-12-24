#include "proc.h"
#include "prototypes.h"

extern struct pcb proctable[NPROC];
extern struct pcb *currproc;
extern struct pcb *idleproc;

void sched_yield(void) {
  // Find next runnable process except for idleproc, and switch to it
  for (int i = 0; i < NPROC; i++) {
    int n = (currproc->pid + i) % NPROC;
    if (proctable[n].pid != IDLEPROC_PID && proctable[n].state == RUNNABLE) {
      // If current process is the only runnable process, do nothing
      if (n == currproc->pid) {
        return;
      }
      struct pcb *prevproc = currproc;
      currproc = &proctable[n];
      switch_context(&prevproc->sp, &currproc->sp);
      return;
    }
  }
  // If there is no runnable process except for idleproc, switch to idleproc
  switch_context(&currproc->sp, &idleproc->sp);
}
