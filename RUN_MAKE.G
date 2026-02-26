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

make