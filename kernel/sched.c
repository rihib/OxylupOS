#include "proc.h"
#include "prototypes.h"

// アイドルプロセス以外の実行可能なプロセスを、現在のプロセスの次のプロセスから順に探し、
// あればそのプロセスにコンテキストスイッチし、もしも実行可能なプロセスが現在のプロセスのみなら何もせずに終了し、
// 現在のプロセスも含めてアイドルプロセス以外に実行可能なプロセスがなければアイドルプロセスにコンテキストスイッチする。

extern struct pcb proctable[NPROC];
extern struct pcb *currproc;
extern struct pcb *idleproc;

void sched_yield(void) {
  for (int i = 0; i < NPROC; i++) {
    int n = (currproc->pid + i) % NPROC;
    if (proctable[n].pid != IDLEPROC_PID && proctable[n].state == RUNNABLE) {
      if (n == currproc->pid) {
        return;
      }
      struct pcb *prevproc = currproc;
      currproc = &proctable[n];
      switch_context(&prevproc->sp, &currproc->sp);
      return;
    }
  }
  switch_context(&currproc->sp, &idleproc->sp);
}
