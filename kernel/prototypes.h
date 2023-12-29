#pragma once

#include "common/types.h"
#include "proc.h"

// main.c
void main(void);

// mem.c
phys_addr_t alloc_pages(int n);

// proc.c
void initidleproc(void);
struct pcb *initproc(uintptr_t pc);
void switch_context(uintptr_t *prev_context, uintptr_t *next_context);

// riscvregs.c
void initregs(void);
void set_mstatus_mpp(char mode);

// sched.c
void sched_yield(void);

// stackinit.S
void initstack(void);

// stdio.c
int printf(const char *fmt, ...);
int putchar(int c);
int puts(const char *s);

// trap.c
void inittrap(void);
void trapentry(void);
void traphandler(void);

// uart.c
void inituart(void);
void uartputchar(uint8_t c, bool_t can_interrupt);
