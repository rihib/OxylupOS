#pragma once

#include "types.h"

// main.c
void main(void);

// regsinit.c
void regsinit(void);

// riscvregs.c
void set_mstatus_mpp(char mode);

// stackinit.S
void stackinit(void);

// stdio.c
void panic(const char *s);
int putchar(int c);
int puts(const char *s);

// uart.c
void uartinit(void);
void uartputchar(uint8_t c, bool_t can_interrupt);
