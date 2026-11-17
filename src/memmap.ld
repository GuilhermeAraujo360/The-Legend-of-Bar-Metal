MEMORY {
    SRAM (rwx) : ORIGIN = 0x402F0400, LENGTH = 0xFC00   /* SRAM interna */
    DDR  (rwx) : ORIGIN = 0x80000000, LENGTH = 512M
}

SECTIONS {
    .text : {
        *(.vectors)
        *(.text*)
        *(.rodata*)
    } > DDR

    .data : {
        *(.data*)
    } > DDR

    .bss : {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        _bss_end = .;
    } > DDR

    /* Stacks no fim da região usada */
    . = ALIGN(8);
    _svc_stack_top = . + 0x4000;   /* 16KB SVC */
    . = _svc_stack_top;
    _irq_stack_top = . + 0x4000;   /* 16KB IRQ */
    . = _irq_stack_top;
}