    xref _do_vbl
	xdef _trap28,_trap28_isr,_vbl_isr

_trap28:
							;trap	#28
			rts

_trap28_isr:
			rte

_vbl_isr:
			movem.l         D0-D1/A0-A1,-(SP)
            jsr             _do_vbl         ;c function will delete saved registers
            movem.l         (SP)+,D0-D1/A0-A1
            rte


