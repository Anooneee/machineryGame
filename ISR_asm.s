	xdef _vbl_isr
	xdef _ikbd_isr

	xref _do_vbl
	xref _do_kbd

	
_vbl_isr:
		movem.l d0-2/a0-2,-(sp) ;save reg's
		jsr _do_vbl
		movem.l (sp)+,d0-2/a0-2 ;restore registers
		rte

_kbd_isr:
		movem.l d0-2/a0-2,-(sp) ;save reg's
		jsr _do_kbd
		movem.l (sp)+,d0-2/a0-2 ;restore registers
		rte