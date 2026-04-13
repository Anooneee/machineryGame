    
	xdef _vbl_isr

_vbl_isr:
		movem.l d0-d2/a0-a2,-(sp)
		jsr _do_vbl
		movem.l (sp)+,d0-d2/a0-a2
		rte