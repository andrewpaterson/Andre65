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


	XDEF	~~DrawSpriteOpaqueUnsafeASM	;void DrawSpriteOpaqueUnsafeASM(uint8_t* puiVideoMemory, uint16_t uiVideoWidth, SSpriteHeader* psSprite)
~~DrawSpriteOpaqueUnsafeASM:
;Local variable space (scratch)

_DSOU_SpriteWidth		EQU	1
_DSOU_SpriteHeight		EQU	3
;Extra space on Stack (mapped as Direct Page $1)
_DSOU_Scratch			EQU	5 							; SW(2) + SH(2) + 1

;Total Stack used
_DSOU_Parameters		EQU	_DSOU_Scratch+3+4+2+4		;RTL address(3) + VM(4) + VW(2) + char(2) + colour(2)
;Parameter Direct Page offsets
_DSOU_SpriteStruct		EQU	_DSOU_Scratch+3+4+2+4-1		;RTL address(3) + VM(4) + VW(2) + char(2) -1
_DSOU_VideoWidth		EQU	_DSOU_Scratch+3+4+2-1		;RTL address(3) + VM(4) + VW(2) -1
_DSOU_VideoMemory		EQU	_DSOU_Scratch+3+4-1			;RTL address(3) + VM(4) -1


;preamble:
	LONGI ON
	LONGA ON
	
	TSC
	SEC
	SBC	#_DSOU_Scratch
	TCS
	PHD
	TCD
	PHX
	PHY
	PHB

;behaviour:
	
	LDY #$2
	LDA [<_DSOU_SpriteStruct-2],Y
	STA <_DSOU_SpriteWidth
	LDY #$4
	LDA [<_DSOU_SpriteStruct-2],Y
	STA <_DSOU_SpriteHeight

	SEP #$20
	LONGA OFF
	
	; LDX #2
	; STA !block_move,X
	; LDA <_DSOU_VideoMemory+2
	; LDX #1
	; STA !block_move,X
	 REP #$20
	 LONGA ON

	CLC
	LDA <_DSOU_SpriteStruct-2
	ADC #6
	TAX
	LDY <_DSOU_VideoMemory
	LDA <_DSOU_SpriteWidth
	DEC

block_move:
	MVN $03, $20

;postamble:
	LDA	<_DSOU_Scratch+2				;RTL hi, RTL lo
	STA	<_DSOU_Parameters-1
	LDA	<_DSOU_Scratch+1				;RTL b, rtl hi
	STA	<_DSOU_Parameters-2
	
	PLB
	PLY
	PLX
	PLD
	TSC
	CLC
	ADC	#_DSOU_Parameters-3
	TCS
	RTL
	