#pragma once

#include "common/types.h"

#define NPROC_LIMIT 8

enum procstate { UNUSED, RUNNABLE };

struct pcb {
  int pid;
  enum procstate state;
  uintptr_t sp;
  uintptr_t kstack[13];
};
