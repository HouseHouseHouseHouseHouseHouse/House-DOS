/* Constants for multiboot header */
.set FLAGS,         ( 1 << 0 | 1 << 1 )
.set MAGIC,         0x1BADB002
.set CHECKSUM,      -(MAGIC + FLAGS)


/* Multiboot Header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


/* Stack Configuration */
.section .bss
.align 16

stack_bottom:
.skip 16384

stack_top:


/* Kernel Initialization */
.section .text
.global _start
.type _start, @function

_start:
    mov $stack_top, %esp
    call main

    cli

nil:
    hlt
    jmp nil


/* Total size of Kernel */
.size _start, . - _start
