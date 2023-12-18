#pragma once

#include "common/types.h"

// main.c
void main(void);

// regsinit.c
void initregs(void);

// riscvregs.c
void set_mstatus_mpp(char mode);

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
