ENTRY(PLATFORM_ENTRY)
OUTPUT_FORMAT(elf64-x86-64)
/*OUTPUT_FORMAT(binary)*/

OFFSET = 0x100000;

SECTIONS {

    . = OFFSET;
    
    .text : AT(ADDR(.text) - OFFSET){
        *(.entry)
        *(.text)
        . = ALIGN(4K);
    }

    .data : AT(ADDR(.data) - OFFSET){
        *(.data)
        . = ALIGN(4K);
    }

    .bss : AT(ADDR(.bss) - OFFSET){
        *(.bss)
        . = ALIGN(4K);
    }

    .rodata : AT(ADDR(.rodata) - OFFSET){
        *(.rodata)
        . = ALIGN(4K);
    }

    .kernel_heap : AT(ADDR(.kernel_heap) - OFFSET){
        . = ALIGN(4K);
    }

    /DISCARD/ : {
        *(.comment)
    }
}