# Test kernel

```bash
% make DEBUG=1
clang -ffreestanding -fno-common -fno-pie -fno-stack-protector -I. -MD -mcmodel=medany -mno-relax -nostdlib -O2 -std=c2x -Wall -Werror -Wextra --target=riscv64 -ggdb3 -gdwarf-5 -DCORES=1 -Wl,-Tkernel/kernel.ld -z max-page-size=4096 -Wl,-Map=kernel/kernel.map -o kernel/kernel.elf common/stdlib.c kernel/main.c kernel/regsinit.c kernel/riscvregs.c kernel/stack.c kernel/stackinit.S kernel/stdio.c kernel/trap.c kernel/uart.c
qemu-system-riscv64 -bios none -global virtio-mmio.force-legacy=false -m 128M -machine virt -nographic --no-reboot -serial mon:stdio -smp 1 -kernel kernel/kernel.elf

bonsaiOS starts booting!!
PANIC: kernel/trap.c:87: unexpected trap scause=2, stval=0, sepc=800000ee

QEMU: Terminated
% llvm-addr2line -e kernel/kernel.elf 800000ee
/Users/rihib/dev/sechack/bonsaiOS/kernel/main.c:17
% make clean
rm -f kernel/kernel.elf kernel/kernel.map common/*.o common/*.d kernel/*.o kernel/*.d
```
