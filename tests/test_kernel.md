# Test kernel

```bash
% make DEBUG=1
clang -ffreestanding -fno-common -fno-pie -fno-stack-protector -I. -MD -mcmodel=medany -mno-relax -nostdlib -O2 -std=c2x -Wall -Werror -Wextra --target=riscv64 -ggdb3 -gdwarf-5 -DNCORE=1 -Wl,-Tkernel/kernel.ld -z max-page-size=4096 -Wl,-Map=kernel/kernel.map -o kernel/kernel.elf common/stdlib.c kernel/main.c kernel/proc.c kernel/riscvregs.c kernel/sched.c kernel/stack.c kernel/stackinit.S kernel/stdio.c kernel/trap.c kernel/uart.c
qemu-system-riscv64 -bios none -global virtio-mmio.force-legacy=false -m 128M -machine virt -nographic --no-reboot -serial mon:stdio -smp 1 -kernel kernel/kernel.elf

OxylupOS starts booting!!
procA
procB
ABABABABABABABABABABABABABAQEMU: Terminated
% make clean
rm -f kernel/kernel.elf kernel/kernel.map common/*.o common/*.d kernel/*.o kernel/*.d
```
