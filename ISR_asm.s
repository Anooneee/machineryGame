    xref _do_vbl
	xdef _vbl_isr

_vbl_isr:
		movem.l d0-2/a0-2,-(sp)
		jsr _do_vbl
		movem.l (sp)+,d0-2/a0-2
		rte