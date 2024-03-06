ENTRY(initstack)

SECTIONS {
  . = 0x80000000;

  .text : ALIGN(4096) {
    KEEP(*(.text.boot));
    *(.text .text.*);
  }

  .rodata : ALIGN(4) {
    *(.rodata .rodata.* .srodata .srodata.*);
  }

  .data : ALIGN(4) {
    *(.data .data.* .sdata .sdata.*);
  }

  .bss : ALIGN(4) {
    *(.bss .bss.* .sbss .sbss.*);
  }

  . = ALIGN(4096);
  PROVIDE(__kernel_end = .);
}
