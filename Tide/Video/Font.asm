	INCLUDE Prolog.inc


; -------------------------------------------------------------------------------------------------------------
;8-bit RGB format bits R0..2 G3..5 B6..7.
;Packs 16-bit R, 16-bit G, 16-bit B value into 8-bit RGB
;
;Remember paramerters are pushed in reverse order (B, G, R)
;16-bit accumulator and 16-bit indices can be assumed.
;
;Direct Page offset one is start of scratch space.
;Stack and Direct Page start at about the same address.


	XDEF	~~DrawFontCharUnsafeASM	;void DrawFontCharUnsafe(uint8_t* puiVideoMemory, uint16_t uiWidth, char c, uint8_t uiColour)
~~DrawFontCharUnsafeASM:
;Local variable space (scratch)

_DFCU_CharMemory	EQU	1
_DFCU_Scratch		EQU	3				;Extra space on Stack (mapped as Direct Page $1)

;Total Stack used
_DFCU_Parameters		EQU	_DFCU_Scratch+3+4+2+2+2		;RTL address(3) + MM(4) + W(2) + char(2) + colour(2)
;Parameter Direct Page offsets
_DFCU_Colour			EQU	_DFCU_Scratch+3+4+2+2+2-1	;RTL address(3) + MM(4) + W(2) + char(2) + colour(2) -1
_DFCU_Char				EQU	_DFCU_Scratch+3+4+2+2-1		;RTL address(3) + MM(4) + W(2) + char(2) -1
_DFCU_Width				EQU	_DFCU_Scratch+3+4+2-1		;RTL address(3) + MM(4) + W(2) -1
_DFCU_VideoMemory		EQU	_DFCU_Scratch+3+4-1			;RTL address(3) + MM(4) -1

	XREF ~~gauiFont5x7Data

preamble:
	LONGI ON
	LONGA ON
	
	TSC
	SEC
	SBC	#_DFCU_Scratch
	TCS
	PHD
	TCD

behaviour:
	PHB
	SEP #$20
	LONGA OFF
	LDA #^~~gauiFont5x7Data
	PHA
	PLB
	REP #$20
	LONGA ON

	LDA <_DFCU_Char
	SEC
	SBC #$20
	STA <_DFCU_Char

	ASL
	ASL
	ASL
	STA <_DFCU_CharMemory; (Char-32) * 8
	
	CLC
	ADC #<~~gauiFont5x7Data ;#(gauiFont5x7Data).low16 + (Char-32) * 8
	STA <_DFCU_CharMemory

	LDA <_DFCU_Colour
	XBA ;A = 0, B = Colour
	SEP #$20
	LONGA OFF

	LDX #0 ;Row = 0
loop_Row:
	TXY
	LDA (<_DFCU_CharMemory),Y ; A = Pixel Pattern, B = Colour
	LDY #5 ;x = 5
	
loop_X:
	LSR
	BCC no_pixel

	XBA ; A = Colour, B = Pixel Pattern
	STA [<_DFCU_VideoMemory-2],Y
	XBA ; A = Pixel Pattern, B = Colour
no_pixel:
	
	DEY
	BNE loop_X

	REP #$20
	LONGA ON
	LDA <_DFCU_VideoMemory-2
	CLC
	ADC <_DFCU_Width
	STA <_DFCU_VideoMemory-2
	
	LDA <_DFCU_Colour
	XBA ;A = 0, B = Colour
	SEP #$20
	LONGA OFF

	;for: Row < 7; Row++
	INX ;Row++
	CPX #7
	BNE loop_Row

	REP #$20
	LONGA ON
	
	PLB

postamble:
	LDA	<_DFCU_Scratch+2				;RTL hi, RTL lo
	STA	<_DFCU_Parameters-1
	LDA	<_DFCU_Scratch+1				;RTL b, rtl hi
	STA	<_DFCU_Parameters-2
	PLD
	TSC
	CLC
	ADC	#_DFCU_Parameters-3
	TCS
	RTL
