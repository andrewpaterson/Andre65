     PW 132         ;Page Width (# of char/line) 
     PL 100000      ;Page Length for HP Laser
     INCLIST ON     ;Add Include files in Listing

	IF	SMALL
	ELSEIF	MEDIUM
	ELSEIF	COMPACT
	ELSEIF	LARGE
	ELSE
		EXIT         "Not Valid 'Model' type - SMALL, MEDIUM, COMPACT, or LARGE: Use -DSMALL, etc."
	ENDIF

	XDEF	~~BlockMove	;extern void BlockMove(void *pvDest, void* pvSource, size_t uiBytes)
~~BlockMove:
;Local variable space (scratch)
_BlockMove_Scratch			EQU	2						;Extra space on Stack (mapped as Direct Page $1)
;Total Stack used
_BlockMove_Parameters		EQU	_BlockMove_Scratch+3+4+4+2	;RTL address + D + S + n
;Parameter Direct Page offsets
_BlockMove_Bytes			EQU	_BlockMove_Scratch+3+4+4+1	;RTL address + D + S + 1 (+ 1 because low byte address first)
_BlockMove_Source			EQU	_BlockMove_Scratch+3+4+1		;RTL address + D + 1 
_BlockMove_Dest				EQU	_BlockMove_Scratch+3+1		;RTL address + 1 

;preamble
	LONGI ON
	LONGA ON
	TSC
	SEC
	SBC	#_BlockMove_Scratch
	TCS
	PHD
	TCD
	PHX
	PHY
	PHB

;behaviour
	LDX <_BlockMove_Source
	LDY <_BlockMove_Dest
	LDA <_BlockMove_Bytes
	MVN $22, $20

;postamble
	LDA	<_BlockMove_Scratch+2				;RTL hi, RTL lo
	STA	<_BlockMove_Parameters-1
	LDA	<_BlockMove_Scratch+1				;RTL b, rtl hi
	STA	<_BlockMove_Parameters-2
	PLB
	PLY
	PLX
	PLD
	TSC
	CLC
	ADC	#_BlockMove_Parameters-3
	TCS
	TXA
	RTL