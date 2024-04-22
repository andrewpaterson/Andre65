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

	XDEF	~~RGB	;unsigned char RGB(unsigned char r, unsigned char g, unsigned char b)
~~RGB:
;Local variable space (scratch)
_RGB_Scratch		EQU	2						;Extra space on Stack (mapped as Direct Page $1)
;Total Stack used
_RGB_Parameters		EQU	_RGB_Scratch+3+2+2+2	;RTL address + r + g + b
;Parameter Direct Page offsets
_RGB_B				EQU	_RGB_Scratch+3+2+2+2-1	;RTL address + r + g + 1 (+ 1 because low byte address first)
_RGB_G				EQU	_RGB_Scratch+3+2+2-1	;RTL address + r + 1 
_RGB_R				EQU	_RGB_Scratch+3+2-1		;RTL address + 1 

;preamble
	LONGI ON
	LONGA ON
	TSC
	SEC
	SBC	#_RGB_Scratch
	TCS
	PHD
	TCD

;behaviour
	LDA <_RGB_B
	ASL
	ASL
	ASL
	ASL
	ASL
	ASL
	STA <1
	LDA <_RGB_G
	AND #7
	ASL
	ASL
	ASL
	ORA <1
	STA <1
	LDA <_RGB_R
	AND #7
	ORA <1	;Result is in Accumulator
	TAX

;postamble
	LDA	<_RGB_Scratch+2				;RTL hi, RTL lo
	STA	<_RGB_Parameters-1
	LDA	<_RGB_Scratch+1				;RTL b, rtl hi
	STA	<_RGB_Parameters-2
	PLD
	TSC
	CLC
	ADC	#_RGB_Parameters-3
	TCS
	TXA
	RTL
