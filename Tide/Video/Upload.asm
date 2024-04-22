	INCLUDE Prolog.inc


STACK   EQU   $EFFF

	XREF  _BEG_DATA
	XREF  _END_DATA
	XREF  _BEG_UDATA
	XREF  _END_UDATA
	XREF  ~~main


START:
	; Initialise Native Mode
	CLC
	XCE
	REP   #$38		;16 bit memory, indexes and clear decimal mode
	LONGI ON
	LONGA ON
	LDA   #STACK
	TCS

	SEP	#$20		;8 bit memory
	LONGA OFF
	LDA	#$49
clear_screen:
	STA	$200000,X
	INX
	BNE	clear_screen

	; Set up the data bank register.
	SEP	#$20		;8 bit memory
	LONGA OFF
	LDA	#^_BEG_DATA  ;get bank of DATA
	PHA
	PLB				;set data bank register
	REP	#$20		;16 bit memory
	LONGA ON

	; Transfer control to the real program.
	JSL   ~~main

WAIT:
        WAI
		JMP WAIT

END

