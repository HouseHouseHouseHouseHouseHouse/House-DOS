/* Load GDT from RAM */
.section .text
.global gdt_load
.type gdt_load, @function

gdt_load:
    movl    4(%esp) , %eax
    movl    %eax    , 2+gdt_desc(,1)

    movw    8(%esp) , %ax
    movw    %ax     , gdt_desc(,1)

    lgdt    gdt_desc(,1)
    ljmp    $0x0008 , $reload_segments

reload_segments:
    movw    $0x0010 , %ax

    movw    %ax     , %ds
    movw    %ax     , %es
    movw    %ax     , %fs
    movw    %ax     , %gs
    movw    %ax     , %ss

    ret

gdt_desc:
    .word 0x0000
    .long 0x00000000
