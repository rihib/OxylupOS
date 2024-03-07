#pragma once

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef uint64_t phys_addr_t;
typedef uint32_t reg_t;

typedef uint32_t size_t;
typedef uint32_t uintptr_t;
typedef uint32_t *pagetable_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef uint8_t bool_t;
#define true 1
#define false 0

#define EOF (-1)
