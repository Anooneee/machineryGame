            xdef    _set_vid_base

_set_vid_base:
            move.l      4(sp),d0        ; load parameter UINT32 *
            lsr.l       #8,d0           ; shift right to move high and low bytes to low word
            lea         $FF8201,a1      ; load video base pointer
            movep.w     d0,0(a1)        ; move high and low to new in one go

            rts             ; Return from subroutine


