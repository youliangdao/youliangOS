.code32
        .extern inthandler21, inthandler2c, inthandler27
        .global io_hlt, io_cli, io_sti, io_stihlt
        .global io_in8, io_in16, io_in32
        .global io_out8, io_out16, io_out32
        .global io_load_eflags, io_store_eflags
        .global load_gdtr, load_idtr
        .global asm_inthandler21, asm_inthandler27, asm_inthandler2c

.text
io_hlt:         # void io_hlt(void) ;
        hlt
        ret
io_cli:         # void io_cli(void);
        cli
        ret
io_sti:         # voi io_sti(void);
        sti
        ret
io_stihlt:      # voi io_stihlt(void);
        sti
        hlt
        ret
io_in8:         # int io_in8(int port);
        movl    4(%esp), %edx   # port
        movl    $0, %eax
        inb     %dx, %al
        ret
io_in16:        # int io_in16(int port);
        movl    4(%esp), %edx   # port
        movl    $0, %eax
        inw     %dx, %ax
        ret
io_in32:        # int io_in32(int port);
        movl    4(%esp), %edx   # port
        movl    $0, %eax
        inl     %dx, %eax
        ret
io_out8:        # int io_out8(int port, int data);
        movl    4(%esp), %edx   # port
        movb    8(%esp), %al    # data
        outb    %al, %dx
        ret
io_out16:       # int io_out16(int port, int data);
        movl    4(%esp), %edx   # port
        movl    8(%esp), %eax    # data
        outw    %ax, %dx
        ret 
io_out32:       # int io_out16(int port, int data);
        movl    4(%esp), %edx   # port
        movl    8(%esp), %eax    # data
        outl    %eax, %dx
        ret

io_load_eflags: # int io_load_eflags(void);
        pushf           # push eflags
        pop     %eax
        ret
io_store_eflags:        # void io_store_eflags(int eflags)
        movl    4(%esp), %eax
        push    %eax
        popf
        ret

load_gdtr:              # void load_gdtr(int limit, int addr)
        movw    4(%esp), %ax    # limit
        movw    %ax, 6(%esp)
        lgdt    6(%esp)
        ret
load_idtr:              # void load_idtr(int limit, int addr)
        movw    4(%esp), %ax    # limit
        movw    %ax, 6(%esp)
        lidt    6(%esp)
        ret

asm_inthandler21:
        pushw   %es
        pushw   %ds
        pusha
        movl    %esp, %eax
        pushl   %eax
        movw    %ss, %ax
        movw    %ax, %ds
        movw    %ax, %es
        call    inthandler21
        popl    %eax
        popa
        popw    %ds
        popw    %es
        iret

asm_inthandler27:
        pushw   %es
        pushw   %ds
        pusha
        movl    %esp, %eax
        pushl   %eax
        movw    %ss, %ax
        movw    %ax, %ds
        movw    %ax, %es
        call    inthandler27
        popl    %eax
        popa
        popw    %ds
        popw    %es
        iret

asm_inthandler2c:
        pushw   %es
        pushw   %ds
        pusha
        movl    %esp, %eax
        pushl   %eax
        movw    %ss, %ax
        movw    %ax, %ds
        movw    %ax, %es
        call    inthandler2c
        popl    %eax
        popa
        popw    %ds
        popw    %es
        iret