#pragma once

#define KERNELBASE 0x80000000
#define PAGESIZE 4096
#define PMEMEND (KERNELBASE + 128 * 1024 * 1024)

#define SATP_MODE_SV32 (1u << 31)
#define PTE_V (1 << 0)
#define PTE_R (1 << 1)
#define PTE_W (1 << 2)
#define PTE_X (1 << 3)
#define PTE_U (1 << 4)

#define IS_ALIGNED(val, align) __builtin_is_aligned(val, align)
