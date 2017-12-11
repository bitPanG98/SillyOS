ENTRY(PLATFORM_ENTRY)
OUTPUT_FORMAT(elf64-x86_64)

OFFSET = 0x100000

SECTIONS{
    . = OFFSET;
    . = ALIGN(4K);
    .text: AT(ADDR(.text) - OFFSET){
        *(.start)
        *(.text)
    }
    . = ALIGN(4K);
    .data: AT(ADDR(.data) - OFFSET){
        *(.data)
    }
    . = ALIGN(4K);
    .bss: AT(ADDR(.bss) - OFFSET){
        *(.bss)
    }
    . = ALIGN(4K);
    .rodata: AT(ADDR(.rodata) - OFFSET){
        *(.rodata)
    }
    . = ALIGN(4K);
    .kernel_heap: AT(ADDR(.tempo_heap) - OFFSET){

    }

    /DISCARD/: {
        *(.comment)
    }
}