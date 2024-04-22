	INCLUDE Prolog.inc


	XDEF	~~BlockMove	;extern void BlockMove(void *pvDest, void* pvSource, size_t uiBytes)
~~BlockMove:
;Local variable space (scratch)
_BlockMove_Scratch			EQU	1						;Extra space on Stack (mapped as Direct Page 1)

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
	PHK
	PLB
	SEP #$30
	LONGA OFF
	LONGI OFF
	LDA <_BlockMove_Source+2
	LDX #2
	STA !Move,X
	LDA <_BlockMove_Dest+2
	LDX #1
	STA !Move,X
	REP #$30
	LONGA ON
	LONGI ON
	LDX <_BlockMove_Source
	LDY <_BlockMove_Dest
	LDA <_BlockMove_Bytes
Move:
	MVN $FF, $FF

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
