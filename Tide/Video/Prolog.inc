	PW 132         ;Page Width (# of char/line) 
	PL 10000       ;Page Length for HP Laser
	INCLIST ON     ;Add Include files in Listing

	IF	USING_816
	ELSE
		EXIT         "Not Valid Processor. Use -DUSING_816"
	ENDIF

	IF	LARGE
	ELSE
		EXIT         "Not Valid 'Model' type.  Use -DLARGE"
	ENDIF
