#pragma once

#include "types.h"

// main.c
void main(void);

// printf.c
void printf(const char *fmt, ...);
void putchar(int c);

// regsinit.c
void regsinit(void);

// riscvregs.c
void set_mstatus_mpp(char mode);

// stackinit.S
void stackinit(void);

// uart.c
void uartinit(void);
void uartputchar(uint8_t c, bool_t can_interrupt);
