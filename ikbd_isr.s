		xref	_keyboard
		xref	_mouse_coords,_mouse_header,_mouse_state
		xdef	_ikbd_isr

_ikbd_isr:	movem.l	d0-2/a0-2,-(sp)

		move.b	$fffffc02.w,d0	; read the scancode

		move.b	_mouse_state,d1
		cmpi.b	#1,d1
		beq	mouse_x
		cmpi.b	#2,d1
		beq	mouse_y		; If mouse_state = 1, treat scancode as x coordinate. If mouse_state = 2, treat as y. Else, proceed.

		move.b	d0,d1
		and.b	#$F8,d1
		cmp.b	#$F8,d1
		bne	keyboard
					; If the scancode indicates a mouse header, proceed. Else, handle as a keyboard input.

		move.b	d0,_mouse_header
		move.b	#1,_mouse_state	; Indicate that the mouse x coord comes next

		bra	handled_ikbd	; input handled, go to the end

mouse_x:	; Handles the x coordinate for the mouse.

		lea	_mouse_coords,a0

		moveq	#0,d1
		move.b	d0,d1
		ext.w	d1
		add.w	d1,(a0)		; mouse_coords[0] += y movement

		move.b	#2,_mouse_state	; Indicate that y coord comes next

					; BOUNDS CHECKING:
		moveq	#0,d1
		move.w	(a0),d1		; d1 = mouse_coords[0]
		cmpi.w	#631,d1
		bgt	x_upper_bounds	; If mouse_coords[0] < 639, continue
		cmpi.w	#0,d1
		blt	x_lower_bounds	; If mouse_coords[0] >= 0, continue

					; DONE BOUNDS CHECKING, the IKBD has been handled
		bra	handled_ikbd

x_upper_bounds:
		move.w	#631,(a0)	; mouse_coords[1] = 390
		bra	handled_ikbd

x_lower_bounds:
		move.w	#0,(a0)		; mouse_coords[1] = 390
		bra	handled_ikbd


mouse_y:	; Handles the y coordinate for the mouse.

		lea	_mouse_coords,a0

		moveq	#0,d1
		move.b	d0,d1
		ext.w	d1
		add.w	d1,2(a0)	; mouse_coords[1] += y movement

		move.b	#0,_mouse_state	; Indicate that the mouse bytestring is over

					; BOUNDS CHECKING:
		moveq	#0,d1
		move.w	2(a0),d1	; d1 = mouse_coords[1]
		cmpi.w	#391,d1
		bgt	y_upper_bounds	; If mouse_coords[1] < 639, continue
		cmpi.w	#0,d1
		blt	y_lower_bounds	; If mouse_coords[1] >= 0, continue

					; DONE BOUNDS CHECKING, the IKBD has been handled
		bra	handled_ikbd

y_upper_bounds:
		move.w	#391,2(a0)	; mouse_coords[1] = 390
		bra	handled_ikbd

y_lower_bounds:
		move.w	#0,2(a0)	; mouse_coords[1] = 0
		bra	handled_ikbd

keyboard:
		moveq	#0,d1
		move.b	d0,d1
		andi.b	#$7F,d1		; d1 = scancode without keypress indicator

		lea	_keyboard,a0
		adda.w	d1,a0		; Increment keyboard[] to access the current key's index.

		btst	#7,d0
		bne	key_release
					; If the scancode indicates a key press, do the following.
		move.b	#0,(a0)		; keyboard[scancode] = 0
		bra	handled_ikbd

key_release:				; If the scancode indicates a key release, do the following
		move.b	#1,(a0)		; keyboard[scancode] = 1

handled_ikbd:
		bclr #6,$fffffa11.w	; clear 

		movem.l	(sp)+,d0-2/a0-2
		rte