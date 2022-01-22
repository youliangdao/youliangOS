.code32
        .global io_hlt
        .global write_mem8
.text
io_hlt:         # void io_hlt(void) ;
        hlt
        ret

write_mem8:     # void write_mem8(int addr, int data);
        movl    4(%esp), %ecx
        movb    8(%esp), %al
        movb    %al, (%ecx)
        ret
