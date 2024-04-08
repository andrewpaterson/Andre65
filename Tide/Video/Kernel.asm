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

startup SECTION 
    ORG $0000

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


        ; Copy the first 5 banks from ROM into RAM
        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$00, #$10

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$01, #$11

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$02, #$12

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$03, #$13

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$04, #$14

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$05, #$15

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$06, #$16

        LDA	#$FFFF
        LDX #$0000
        LDY #$0000
        MVN #$07, #$17

        ; Set RAM/ROM mapping and fast clock
        SEP	#$30
        LONGA	OFF
        LONGI	OFF
        LDA #$40			; bank switch ROM/RAM

        STA $380000
        LDA #$80
        STA $280001			; change to 12.5MHz

        SEP	#$20
        LONGA	OFF
        REP	#$10
        LONGI	ON
        LDX	#$0000
        LDA	#$A4
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
        WAI
	ENDIF

    ;   Install C IRG Handler
	IF	SMALL
		XREF	__IRQHandler
	ELSEIF	MEDIUM
		XREF	~_IRQHandler
	ELSEIF	COMPACT
		XREF	_~IRQHandler
	ELSEIF	LARGE
		XREF	~~IRQHandler
	ENDIF


IRQ:	
		LONGA	ON
		LONGI	ON
		rep	#$30
				;Example of needing to read/write to data in another data bank
	IF	SMALL
	ELSEIF	MEDIUM
		plb		; set data bank register to _DATA
		phd		; save Direct Page Register
	ELSEIF	COMPACT
	ELSEIF	LARGE
		phb		; save Data Bank
		phd		; save Direct Page Register
	ENDIF
		pha
		phx
		phy
	IF	SMALL
		jsr		__IRQHandler
	ELSEIF	MEDIUM
		jsl		~_IRQHandler
	ELSEIF	COMPACT
		jsr		_~IRQHandler
	ELSEIF	LARGE
		jsl		~~IRQHandler
	ENDIF
		ply
		plx
		pla
	IF	SMALL
	ELSEIF	MEDIUM
		pld		; restore Direct Page Reg
		plb		; Restore Data Bank
	ELSEIF	COMPACT
	ELSEIF	LARGE
		pld		; restore Direct Page Reg
		plb		; Restore Data Bank
	ENDIF
		RTI

Undefined_IRQ:
        SEP	#$20
        LONGA	OFF
        REP	#$10
        LONGI	ON
        LDX	#$0000
        LDA	#$07
    red_screen:
        STA	 $200000,X
        INX
        BNE	 red_screen
        LDA	#$00
    black_screen:
        STA	 $200000,X
        INX
        BNE	 black_screen
        jmp Undefined_IRQ
	ENDS

vectors:	SECTION
	IF USING_816
					;65C816 Vectors
        ORG $FFE4

		dw	Undefined_IRQ	; $FFE4 - COP(816)
		dw	Undefined_IRQ	; $FFE6 - BRK(816)
		dw	Undefined_IRQ	; $FFE8 - ABORT(816)
		dw	Undefined_IRQ	; $FFEA - NMI(816)
		dw	Undefined_IRQ	; $FFEC - IRQRVD(816)
		dw	IRQ	            ; $FFEE - IRQ(816)

		dw	Undefined_IRQ	; $FFF0 - IRQRVD(816)
		dw	Undefined_IRQ	; $FFF2 - IRQRVD(816)
		dw	Undefined_IRQ	; $FFF4 - COP(816Emulation)
		dw	Undefined_IRQ	; $FFF6 - IRQRVD(816Emulation)
		dw	Undefined_IRQ	; $FFF8 - ABORT(816Emulation)

					; Common Vectors for all CPUs
		dw	Undefined_IRQ	; $FFFA -  NMIRQ (ALL)
		dw	START		; $FFFC -  RESET (ALL)
		dw	Undefined_IRQ	; $FFFE -  IRQBRK (ALL)
	ENDIF
    ENDS
    END

