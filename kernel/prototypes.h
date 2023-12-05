#pragma once

// main.c
void main(void);

// regsinit.c
void regsinit(void);

// riscvregs.c
void set_mstatus_mpp(char mode);

// stackinit.S
void stackinit(void);
