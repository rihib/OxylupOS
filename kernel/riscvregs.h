#pragma once

#include "common/types.h"

// FIXME: Maybe macros are better?
// FIXME: Better to remove duplicated code

// Machine-Level CSRs
static inline reg_t read_mhartid(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, mhartid" : "=r"(val));
  return val;
}

static inline reg_t read_mstatus(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, mstatus" : "=r"(val));
  return val;
}

static inline void write_mstatus(reg_t val) {
  __asm__ __volatile__("csrw mstatus, %0" : : "r"(val));
}

static inline void write_medeleg(reg_t val) {
  __asm__ __volatile__("csrw medeleg, %0" : : "r"(val));
}

static inline void write_mideleg(reg_t val) {
  __asm__ __volatile__("csrw mideleg, %0" : : "r"(val));
}

static inline void write_mepc(reg_t val) {
  __asm__ __volatile__("csrw mepc, %0" : : "r"(val));
}

// Physical Memory Protection CSRs
static inline void write_pmpaddr0(reg_t val) {
  __asm__ __volatile__("csrw pmpaddr0, %0" : : "r"(val));
}

static inline void write_pmpcfg0(reg_t val) {
  __asm__ __volatile__("csrw pmpcfg0, %0" : : "r"(val));
}

// Supervisor CSRs
static inline reg_t read_stvec(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, stvec" : "=r"(val));
  return val;
}

static inline void write_stvec(reg_t val) {
  __asm__ __volatile__("csrw stvec, %0" : : "r"(val));
}

static inline reg_t read_sie(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, sie" : "=r"(val));
  return val;
}

static inline void write_sie(reg_t val) {
  __asm__ __volatile__("csrw sie, %0" : : "r"(val));
}

static inline reg_t read_sepc(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, sepc" : "=r"(val));
  return val;
}

static inline void write_sepc(reg_t val) {
  __asm__ __volatile__("csrw sepc, %0" : : "r"(val));
}

static inline reg_t read_scause(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, scause" : "=r"(val));
  return val;
}

static inline void write_scause(reg_t val) {
  __asm__ __volatile__("csrw scause, %0" : : "r"(val));
}

static inline reg_t read_stval(void) {
  reg_t val;
  __asm__ __volatile__("csrr %0, stval" : "=r"(val));
  return val;
}

static inline void write_stval(reg_t val) {
  __asm__ __volatile__("csrw stval, %0" : : "r"(val));
}

static inline void write_satp(reg_t val) {
  __asm__ __volatile__("csrw satp, %0" : : "r"(val));
}

// Others
static inline reg_t read_tp(void) {
  reg_t val;
  __asm__ __volatile__("mv %0, tp" : "=r"(val));
  return val;
}

static inline void write_tp(reg_t val) {
  __asm__ __volatile__("mv tp, %0" : : "r"(val));
}
