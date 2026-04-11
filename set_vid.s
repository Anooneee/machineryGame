            xdef    _set_vid_base

_set_vid_base:
            move.l  4(sp),a0        ; load parameter UINT32 * here
            move.l  a0,d0           ; copy address so i can do stuff with it
            lsr.l   #8,d0           ; shift so high and mid bytes are in d0 low word
            movep.w d0,$FF8200      ; write both bytes into vid base address 
            rts