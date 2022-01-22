.code32
        .global io_hlt
.text
io_hlt:     # void io_hlt(void) ;
        hlt
        ret