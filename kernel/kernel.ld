ENTRY(initstack)

SECTIONS {
  . = 0x80000000; /* QEMU */
  __kernel_base = .;

  .text : ALIGN(4096) {
    KEEP(*(.text.boot));
    *(.text .text.*);
  }

  .rodata : ALIGN(16) {
    *(.rodata .rodata.* .srodata .srodata.*);
  }

  .data : ALIGN(16) {
    *(.data .data.* .sdata .sdata.*);
  }

  .bss : ALIGN(16) {
    *(.bss .bss.* .sbss .sbss.*);
  }

  . = ALIGN(4096);
  __ram_start = .;
  . += 64 * 1024 * 1024;
  __ram_end = .;
}
