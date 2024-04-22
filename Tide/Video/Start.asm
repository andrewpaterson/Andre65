	INCLUDE Prolog.inc


STACK   EQU   $EFFF

	XREF	_BEG_DATA
	XREF	_END_DATA
	XREF	_BEG_UDATA
	XREF	_END_UDATA
	XREF	~~IRQHandler
	XREF	~~main


STARTUP SECTION 
	ORG $0000


START:
	; Initialise Native Mode
	CLC
	XCE
	REP   #$38         ;16 bit registers and clear decimal mode
	LONGI ON
	LONGA ON
	LDA   #STACK
	TCS


	; Copy the first 8 banks from ROM into RAM
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

; Transfer control to the real program.
	JSL	~~main
WAIT:
	WAI
	JMP WAIT

    ;   Install C IRG Handler


IRQ:	
		LONGA	ON
		LONGI	ON
		rep	#$30

		PHB		; save Data Bank
		PHD		; save Direct Page Register

		PHA
		PHX
		PHY
		
		JSL		~~IRQHandler

		PLY
		PLX
		PLA
		
		PLD		; restore Direct Page Reg
		PLB		; Restore Data Bank
		
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

VECTORS	SECTION
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
    ENDS
    END

