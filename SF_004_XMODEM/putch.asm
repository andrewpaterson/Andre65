CODE

; ACIA
ACIA_BUFFER			EQU		$0800	; buffer location
ACIA_BUFFER_HEAD	EQU		$083E	; circular buffer head index
ACIA_BUFFER_TAIL	EQU		$083F	; circular buffer tail index
ACIA_BUFFER_SIZE	EQU		62		; buffer size

ACIA_DATA			EQU		$300000
ACIA_STATUS			EQU		$300001
ACIA_COMMAND		EQU		$300002
ACIA_CONTROL		EQU		$300003


_putch: 	STA	ACIA_DATA
			PHX
			LDX #50
loop:		DEX
			NOP
			NOP
			NOP
			BNE loop
			PLX
			RTS


; note that a function like unsigned char get_byte(void)
; will actually return an unsigned int
; where the high byte is in X and the low byte is in A


_acia_has_byte: SEI						; disable IRQ interupts
				LDX #0
				LDA ACIA_BUFFER_HEAD	; fetch head index
				CMP ACIA_BUFFER_TAIL	; compare to tail
				BEQ	index_match			; 
				
				LDA #1					; return 1 if new data in buffer
				CLI
				RTS
				
index_match:	LDA #0					; load A and X with 0
				CLI						; enable IRQ interrupts
				RTS						; return 0...no new data
				
				
				
_getch:	SEI						; disable interrupts
		LDY ACIA_BUFFER_TAIL	; load Y with tail index
		LDA ACIA_BUFFER,Y		; fecth latest byte ACIA_BUFFER[ACIA_BUFFER_TAIL]
		LDX #0					; x is upper byte...make it 0
		INY						; increment y
		CPY #ACIA_BUFFER_SIZE	; compare y to ACIA_BUFFER_SIZE
		BNE savey				; if we reach ACIA_BUFFER_SIZE 
		LDY	#0					; then roll over to 0
savey:
		STY ACIA_BUFFER_TAIL	; save y back to ACIA_BUFFER_TAIL
		CLI						; enable interrupts
		RTS

END