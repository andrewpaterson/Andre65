#include "string.h"
#include "stdlib.h"

#define XMODEM_NAK	0x15
#define XMODEM_ACK	0x06
#define XMODEM_SOH	0x01
#define XMODEM_EOT	0x04

#define XMODEM_WAITING			0
#define XMODEM_RX_SEQ			1
#define XMODEM_RX_NOT_SEQ		2
#define XMODEM_RX_DATA			3
#define XMODEM_RX_CSUM			4

#define WITHOUT_CRLF	0
#define WITH_CRLF		1

#define XMODEM_DEST_ADDRESS	0x00F0	//	(16-BIT)	destination address


extern unsigned char acia_has_byte(void);
extern unsigned char getch(void);
extern void putch(unsigned char b);


void ACIA_Print(char *data,unsigned char crlf);


unsigned char byte;
char WrkSpc[40];


unsigned char xmodem_buffer[128];
unsigned char xmodem_buffer_index = 0;
unsigned char xmodem_state = XMODEM_WAITING;
unsigned char xmodem_seq = 0;
unsigned int  timer = 0xffff;
unsigned char csum;

unsigned char bank;


void main(void)
{
	unsigned char	i;
	unsigned char 	busy;
	unsigned int 	addr;
	unsigned char	errors;

	
	errors = 0;
	addr = PEEKW(XMODEM_DEST_ADDRESS);
	ACIA_Print("XMODEM",WITH_CRLF);
	if(addr == 0xA000) // if the starting address is 0xA000 then we are transfering a file to banked memory 512Kbytes
	{
		ACIA_Print("TO BANK",WITH_CRLF);
		bank = 0;
		EXTENDED_RAM_ROM_BANK_SWITCH_WRITE(bank);
	}
	
	busy = 1;
	
	while(busy)
	{
		if(acia_has_byte() == 1)
		{
			byte = getch();
			switch(xmodem_state)
			{
				case XMODEM_WAITING : 	if(byte == XMODEM_SOH) { xmodem_state =  XMODEM_RX_SEQ; }
										if(byte == XMODEM_EOT) 
										{ 
											busy = 0; 
											xmodem_state = XMODEM_WAITING;											
											putch(XMODEM_ACK);
										}
										break;	
				case XMODEM_RX_SEQ :	xmodem_seq = byte;	
										utoa(xmodem_seq,WrkSpc,16);
										xmodem_state = XMODEM_RX_NOT_SEQ;
										break;
				case XMODEM_RX_NOT_SEQ: xmodem_state = XMODEM_RX_DATA;
										xmodem_buffer_index = 0;
										csum = 0;
										break;
				case XMODEM_RX_DATA :	csum = csum + byte;
										xmodem_buffer[xmodem_buffer_index++] = byte;
										if(xmodem_buffer_index >= 128) xmodem_state = XMODEM_RX_CSUM; 
										break;
				case XMODEM_RX_CSUM :	if(csum == byte)
										{
											for(i=0;i<128;i++)
											{
												POKE(addr++,xmodem_buffer[i]);
											}
											if(addr == 0xC000) 		// check if address has reached 0xBFFF...if so 8K has loaded start again at 0xA000
											{
												bank++;				// point to next 8K memory bank
												EXTENDED_RAM_ROM_BANK_SWITCH_WRITE(bank);	// write to bank register
												
												addr = 0xA000;		// reset addr back to the start of this 8K bank
												
											}
											putch(XMODEM_ACK);
											
										}
										else
										{
											putch(XMODEM_NAK);
											xmodem_state = XMODEM_WAITING;
											errors++;
										}
										xmodem_state = XMODEM_WAITING;
										timer = 0xFFFF;
										break;
				default : 	xmodem_state = XMODEM_WAITING;
							break;
			}
		}
		timer--;
//		if(timer == 0x8000) LED_LATCH_WRITE(2);
		if(timer == 0)
		{
			timer = 0xFFFF;
			xmodem_state = XMODEM_WAITING;
			putch(XMODEM_NAK);
//			LED_LATCH_WRITE(0x03);
			
		}
	}
	ACIA_Print("ERR PKT ",WITHOUT_CRLF);
	utoa(errors,WrkSpc,16);
	ACIA_Print(WrkSpc,WITH_CRLF);
	ACIA_Print("TRANSFER COMPLETE ",WITH_CRLF);


}

void ACIA_Print(char *data,unsigned char crlf)
{
	
	while(*data)
	{
		putch(*data++);
	}
	
	if(crlf == 1)
	{
		putch(0x0d);
		putch(0x0a);	
	}
	
}
