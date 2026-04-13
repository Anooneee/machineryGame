            xdef    _set_video_base

_set_video_base:
            link        a6,#0
            movem.l     d0-d2/a0-a1,-(sp)

            move.l      8(a6),d2        ; load parameter UINT32 *
            lsr.l       #8,d2           ; shift right to move high and low bytes to low word

                                        ; Enter super to access volitile memory
            clr.l   -(sp)               ; enter supervisor mode with user stack
            move.w  #$20,-(sp)
            trap    #1
            addq.l  #6,sp
            

            lea         $FF8201,a1      ; load video base pointer
            movep.w     d2,0(a1)        ; move high and low to new in one go

                                        ; Exit super
            move.l  d0,-(sp)   ; return to user mode, restoring
            move.w  #$20,-(sp)          ;   system stack pointer
            trap    #1
            addq.l  #6,sp
            movem.l (sp)+,d0-d2/a0-a1

            unlk    a6
            rts             ; Return from subroutine