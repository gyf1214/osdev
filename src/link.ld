ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
    GlobalOffset = 0xc0000000;
    . = 1M + GlobalOffset;

    .text ALIGN(4K) : AT(ADDR(.text) - GlobalOffset) {
        *(.multiboot)
        *(.text)
        *(.rodata*)
    }

    .data ALIGN(4K) : AT(ADDR(.data) - GlobalOffset) {
        *(.data)
    }

    .bss ALIGN(4K) : AT(ADDR(.bss) - GlobalOffset) {
        *(COMMON)
        *(.bss)
    }

    kBSSEnd = ALIGN(4);

    kStack = 4M + GlobalOffset;
}
