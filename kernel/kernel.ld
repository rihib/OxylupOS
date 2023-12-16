ENTRY(stackinit)

SECTIONS {
  . = 0x80000000; /* QEMU */

  .text : ALIGN(4096) {
    KEEP(*(.text.boot));
    *(.text .text.*)
  }

  .rodata : ALIGN(16) {
    *(.rodata .rodata.* .srodata .srodata.*)
  }

  .data : ALIGN(16) {
    *(.data .data.* .sdata .sdata.*)
  }

  .bss : ALIGN(16) {
    *(.bss .bss.* .sbss .sbss.*)
  }
}
