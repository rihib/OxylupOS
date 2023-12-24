#pragma once

#include "common/types.h"

#define NPROC 8
#define IDLEPROC_PID -1

enum procstate { UNUSED, RUNNABLE };

struct pcb {
  int pid;
  enum procstate state;
  uintptr_t sp;
  uintptr_t kstack[13];
};
