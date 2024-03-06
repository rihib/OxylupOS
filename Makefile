C = common
K = kernel

C_SRCS = \
	$C/stdlib.c
K_SRCS = \
	$K/main.c \
	$K/mem.c \
	$K/proc.c \
	$K/riscvregs.c \
	$K/sched.c \
	$K/stack.c \
	$K/stackinit.S \
	$K/stdio.c \
	$K/trap.c \
	$K/uart.c

C_OBJS = $(C_SRCS:.c=.o)
K_OBJS = $(K_SRCS:.c=.o)
K_OBJS := $(K_OBJS:.S=.o)
DEPS = $(C_OBJS:.o=.d) $(K_OBJS:.o=.d)
DEPS := $(DEPS:.S=.d)

-include $(DEPS)

# Compiler
CC = clang
CDEBUGFLAGS = \
	-ggdb3 \
	-gdwarf-5
CFLAGS = \
	-ffreestanding \
	-fno-common \
	-fno-pie \
	-fno-stack-protector \
	-I. \
	-MD \
	-mcmodel=medany \
	-mno-relax \
	-nostdlib \
	-O2 \
	-std=c2x \
	-Wall \
	-Werror \
	-Wextra
# -nopie
LDDEBUGFLAGS = \
	-Wl,-Map=$K/kernel.map
LDFLAGS = \
	-Wl,-T$K/kernel.ld \
  -z max-page-size=4096

# QEMU
QEMU32 = qemu-system-riscv32
QEMU64 = qemu-system-riscv64
QEMUDEBUGOPTS = \
	--no-reboot \
	-serial mon:stdio
QEMUOPTS = \
	-bios none \
	-global virtio-mmio.force-legacy=false \
	-m 128M \
	-machine virt \
	-nographic

ifeq ($(BIT),64)
	CFLAGS += --target=riscv64
	QEMU = $(QEMU64)
else
	CFLAGS += --target=riscv32
	QEMU = $(QEMU32)
endif

ifdef DEBUG
	CFLAGS += $(CDEBUGFLAGS)
	LDFLAGS += $(LDDEBUGFLAGS)
  QEMUOPTS += $(QEMUDEBUGOPTS)
endif

ifdef GDB
	QEMUOPTS += -S -gdb tcp::25501
endif

ifdef NCORE
	CFLAGS += -DNCORE=$(NCORE)
	QEMUOPTS += -smp $(NCORE)
else
	CFLAGS += -DNCORE=1
	QEMUOPTS += -smp 1
endif

.PHONY: all run clean

all: run

run: $K/kernel.elf
	$(QEMU) $(QEMUOPTS) -kernel $K/kernel.elf

$K/kernel.elf: $(C_SRCS) $(K_SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(C_SRCS) $(K_SRCS)

clean:
	rm -f $K/kernel.elf $K/kernel.map $C/*.o $C/*.d $K/*.o $K/*.d
