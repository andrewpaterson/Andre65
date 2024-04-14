#include "string.h"
#include "stdlib.h"
#include "inttypes.h"
#include "Circle.h"


void Pause(uint32_t uiDelay)
{
	uint32_t x;
	for (x = 0; x < uiDelay; x++)
	{
#asm
	nop
#endasm	
	}
	return;
}

unsigned char* guiVideoMemory;


void DrawBlockTest(uint16_t uiBlock, uint16_t uiColour)
{
    unsigned short xs;
	for (xs = uiBlock*4*320; xs < uiBlock*4*320 + 320*4; xs++)
	{
		*(guiVideoMemory + xs) = uiColour;
	}
}


extern unsigned char RGB(uint16_t r, uint16_t g, uint16_t b);


unsigned char RGBSlow(uint16_t r, uint16_t g, uint16_t b)
{
	return (r & 0x7) | ((g & 0x7) << 3) | ((b & 0x3) << 6);
}

void main(void)
{
	uint8_t	t;
	unsigned int y;
	unsigned char c;
	void*	pv;
	
	guiVideoMemory = (unsigned char*)0x200000;
	y = 0;
	
	pv = malloc(3);
	free(pv);
	
	DrawBlockTest(y++, RGB(7, 7, 3));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(1, 0, 0));
	DrawBlockTest(y++, RGB(2, 0, 0));
	DrawBlockTest(y++, RGB(3, 0, 0));
	DrawBlockTest(y++, RGB(4, 0, 0));
	DrawBlockTest(y++, RGB(5, 0, 0));
	DrawBlockTest(y++, RGB(6, 0, 0));
	DrawBlockTest(y++, RGB(7, 0, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 1, 0));
	DrawBlockTest(y++, RGB(0, 2, 0));
	DrawBlockTest(y++, RGB(0, 3, 0));
	DrawBlockTest(y++, RGB(0, 4, 0));
	DrawBlockTest(y++, RGB(0, 5, 0));
	DrawBlockTest(y++, RGB(0, 6, 0));
	DrawBlockTest(y++, RGB(0, 7, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 1));
	DrawBlockTest(y++, RGB(0, 0, 1));
	DrawBlockTest(y++, RGB(0, 0, 2));
	DrawBlockTest(y++, RGB(0, 0, 2));
	DrawBlockTest(y++, RGB(0, 0, 3));
	DrawBlockTest(y++, RGB(0, 0, 3));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(1, 1, 0));
	DrawBlockTest(y++, RGB(2, 2, 0));
	DrawBlockTest(y++, RGB(3, 3, 0));
	DrawBlockTest(y++, RGB(4, 4, 0));
	DrawBlockTest(y++, RGB(5, 5, 0));
	DrawBlockTest(y++, RGB(6, 6, 0));
	DrawBlockTest(y++, RGB(7, 7, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(1, 0, 0));
	DrawBlockTest(y++, RGB(2, 0, 1));
	DrawBlockTest(y++, RGB(3, 0, 1));
	DrawBlockTest(y++, RGB(4, 0, 2));
	DrawBlockTest(y++, RGB(5, 0, 2));
	DrawBlockTest(y++, RGB(6, 0, 3));
	DrawBlockTest(y++, RGB(7, 0, 3));
	
	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 1, 0));
	DrawBlockTest(y++, RGB(0, 2, 1));
	DrawBlockTest(y++, RGB(0, 3, 1));
	DrawBlockTest(y++, RGB(0, 4, 2));
	DrawBlockTest(y++, RGB(0, 5, 2));
	DrawBlockTest(y++, RGB(0, 6, 3));
	DrawBlockTest(y++, RGB(0, 7, 3));
	
	DrawBlockTest(y++, RGB(7, 7, 3));
	
	for (;;)
	{
	}
    return;
}


void IRQHandler(void)
{
    return;
}

