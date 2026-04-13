foreach i { *.o }
	if { -f $i }
		echo Rm $i
		Rm $i
	endif
endfor

foreach i { *.tos }
	if { -f $i }
		echo Rm $i
		Rm $i
	endif
endfor

gen -L2 set_vid.s
gen -L2 ikbd_isr.s
gen -L2 isr_asm.s

make