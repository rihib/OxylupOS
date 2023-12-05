#pragma once

#include "types.h"

// Machine-Level CSRs
static inline uint64_t read_mhartid(void) {
  uint64_t val;
  __asm__ __volatile__("csrr %0, mhartid" : "=r"(val));
  return val;
}

static inline uint64_t read_mstatus(void) {
  uint64_t val;
  __asm__ __volatile__("csrr %0, mstatus" : "=r"(val));
  return val;
}

static inline void write_mstatus(uint64_t val) {
  __asm__ __volatile__("csrw mstatus, %0" : : "r"(val));
}

static inline void write_medeleg(uint64_t val) {
  __asm__ __volatile__("csrw medeleg, %0" : : "r"(val));
}

static inline void write_mideleg(uint64_t val) {
  __asm__ __volatile__("csrw mideleg, %0" : : "r"(val));
}

static inline void write_mepc(uint64_t val) {
  __asm__ __volatile__("csrw mepc, %0" : : "r"(val));
}

// Physical Memory Protection CSRs
static inline void write_pmpaddr0(uint64_t val) {
  __asm__ __volatile__("csrw pmpaddr0, %0" : : "r"(val));
}

static inline void write_pmpcfg0(uint64_t val) {
  __asm__ __volatile__("csrw pmpcfg0, %0" : : "r"(val));
}

// Supervisor CSRs
static inline uint64_t read_sie(void) {
  uint64_t val;
  __asm__ __volatile__("csrr %0, sie" : "=r"(val));
  return val;
}

static inline void write_sie(uint64_t val) {
  __asm__ __volatile__("csrw sie, %0" : : "r"(val));
}

static inline void write_satp(uint64_t val) {
  __asm__ __volatile__("csrw satp, %0" : : "r"(val));
}

// Other Registers
static inline void write_tp(uint64_t val) {
  __asm__ __volatile__("mv tp, %0" : : "r"(val));
}
