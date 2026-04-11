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

gen -L2 ikbd_isr.s

make