    
	xdef _vbl_isr

_vbl_isr:
		movem.l d0-2/a0-2,-(sp)
		jsr 
		movem.l (sp)+,d0-2/a0-2
		rte