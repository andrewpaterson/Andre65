     PW 132         ;Page Width (# of char/line) 
     PL 100000      ;Page Length for HP Laser
     INCLIST ON     ;Add Include files in Listing

	IF	USING_816
	ELSE
		EXIT         "Not Valid Processor: Use -DUSING_816"
	ENDIF


	IF	SMALL
	ELSEIF	MEDIUM
	ELSEIF	COMPACT
	ELSEIF	LARGE
	ELSE
		EXIT         "Not Valid 'Model' type - SMALL, MEDIUM, COMPACT, or LARGE: Use -DSMALL, etc."
	ENDIF


	IF	USING_816
		IF	SMALL
			title  "C Startup Program for Small Model W65C816"
			sttl
		ELSEIF	MEDIUM
			title  "C Startup Program for Medium Model W65C816"
			sttl
		ELSEIF	COMPACT
			title  "C Startup Program for Compact Model W65C816"
			sttl
		ELSEIF	LARGE
			title  "C Startup Program for Large Model W65C816"
			sttl
		ENDIF
	ENDIF


STACK   EQU   $FF7F

    XREF  _BEG_DATA
    XREF  _END_DATA
    XREF  _ROM_BEG_DATA
    XREF  _BEG_UDATA
    XREF  _END_UDATA


;    ORG $0000

	IF	SMALL
		xdef	__START
__START:
	ELSEIF	MEDIUM
		xdef	~_START
~_START:
	ELSEIF	COMPACT
		xdef	_~START
_~START:
	ELSEIF	LARGE
		xdef	~~START
~~START:
	ENDIF

START:
        ; Initialise Native Mode
        CLC
        XCE
        REP   #$38         ;16 bit registers and clear decimal mode
        LONGI ON
        LONGA ON
        LDA   #STACK
        TCS

    clear_screen:
        STA	 $200000,X
        INX
        BNE	 clear_screen

        ; Set up the data bank register.
        SEP   #$20         ;8 bit accum
        LONGA OFF
        LDA   #^_BEG_DATA  ;get bank of data
        PHA
        PLB                ;set data bank register
        REP   #$20         ;16 bit accum
        LONGA ON

    ;   Finally, transfer control to the real program.
	IF	SMALL
        XREF  __main
        JSR   >__main
        WAI
	ELSEIF	MEDIUM
        XREF  ~_main
        JSL   ~_main
        WAI
	ELSEIF	COMPACT
        XREF  _~main
        JSR   _~main
        WAI
	ELSEIF	LARGE
        XREF  ~~main
        JSL   ~~main
	ENDIF
WAIT:
        WAI
		JMP WAIT

    END

