#pragma once

#include "common/types.h"

// FIXME: Maybe macros are better?
// FIXME: Better to remove duplicated code

// Machine-Level CSRs
static inline phys_addr_t read_mhartid(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, mhartid" : "=r"(val));
  return val;
}

static inline phys_addr_t read_mstatus(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, mstatus" : "=r"(val));
  return val;
}

static inline void write_mstatus(phys_addr_t val) {
  __asm__ __volatile__("csrw mstatus, %0" : : "r"(val));
}

static inline void write_medeleg(phys_addr_t val) {
  __asm__ __volatile__("csrw medeleg, %0" : : "r"(val));
}

static inline void write_mideleg(phys_addr_t val) {
  __asm__ __volatile__("csrw mideleg, %0" : : "r"(val));
}

static inline void write_mepc(phys_addr_t val) {
  __asm__ __volatile__("csrw mepc, %0" : : "r"(val));
}

// Physical Memory Protection CSRs
static inline void write_pmpaddr0(phys_addr_t val) {
  __asm__ __volatile__("csrw pmpaddr0, %0" : : "r"(val));
}

static inline void write_pmpcfg0(phys_addr_t val) {
  __asm__ __volatile__("csrw pmpcfg0, %0" : : "r"(val));
}

// Supervisor CSRs
static inline phys_addr_t read_stvec(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, stvec" : "=r"(val));
  return val;
}

static inline void write_stvec(phys_addr_t val) {
  __asm__ __volatile__("csrw stvec, %0" : : "r"(val));
}

static inline phys_addr_t read_sie(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, sie" : "=r"(val));
  return val;
}

static inline void write_sie(phys_addr_t val) {
  __asm__ __volatile__("csrw sie, %0" : : "r"(val));
}

static inline phys_addr_t read_sepc(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, sepc" : "=r"(val));
  return val;
}

static inline void write_sepc(phys_addr_t val) {
  __asm__ __volatile__("csrw sepc, %0" : : "r"(val));
}

static inline phys_addr_t read_scause(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, scause" : "=r"(val));
  return val;
}

static inline void write_scause(phys_addr_t val) {
  __asm__ __volatile__("csrw scause, %0" : : "r"(val));
}

static inline phys_addr_t read_stval(void) {
  phys_addr_t val;
  __asm__ __volatile__("csrr %0, stval" : "=r"(val));
  return val;
}

static inline void write_stval(phys_addr_t val) {
  __asm__ __volatile__("csrw stval, %0" : : "r"(val));
}

static inline void write_satp(phys_addr_t val) {
  __asm__ __volatile__("csrw satp, %0" : : "r"(val));
}

// Others
static inline phys_addr_t read_tp(void) {
  phys_addr_t val;
  __asm__ __volatile__("mv %0, tp" : "=r"(val));
  return val;
}

static inline void write_tp(phys_addr_t val) {
  __asm__ __volatile__("mv tp, %0" : : "r"(val));
}
