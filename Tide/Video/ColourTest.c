#include "Image.h"
#include "ColourTest.h"


void DrawBlockTest(uint16_t uiBlock, uint16_t uiColour)
{
    unsigned short 	xs;
	uint8_t*		pui;
	
	pui = GetImageMemory();
	for (xs = uiBlock*2*320; xs < uiBlock*2*320 + 320*2; xs++)
	{
		*(pui + xs) = uiColour;
	}
}


void DrawColourTest(void)
{
	uint16_t		y;

	y = 0;

	DrawBlockTest(y++, RGB(7, 7, 3));
	DrawBlockTest(y++, RGB(3, 3, 1));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(1, 0, 0));
	DrawBlockTest(y++, RGB(2, 0, 0));
	DrawBlockTest(y++, RGB(3, 0, 0));
	DrawBlockTest(y++, RGB(4, 0, 0));
	DrawBlockTest(y++, RGB(5, 0, 0));
	DrawBlockTest(y++, RGB(6, 0, 0));
	DrawBlockTest(y++, RGB(7, 0, 0));
	DrawBlockTest(y++, RGB(7, 0, 0));
	DrawBlockTest(y++, RGB(6, 0, 0));
	DrawBlockTest(y++, RGB(5, 0, 0));
	DrawBlockTest(y++, RGB(4, 0, 0));
	DrawBlockTest(y++, RGB(3, 0, 0));
	DrawBlockTest(y++, RGB(2, 0, 0));
	DrawBlockTest(y++, RGB(1, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 1, 0));
	DrawBlockTest(y++, RGB(0, 2, 0));
	DrawBlockTest(y++, RGB(0, 3, 0));
	DrawBlockTest(y++, RGB(0, 4, 0));
	DrawBlockTest(y++, RGB(0, 5, 0));
	DrawBlockTest(y++, RGB(0, 6, 0));
	DrawBlockTest(y++, RGB(0, 7, 0));
	DrawBlockTest(y++, RGB(0, 7, 0));
	DrawBlockTest(y++, RGB(0, 6, 0));
	DrawBlockTest(y++, RGB(0, 5, 0));
	DrawBlockTest(y++, RGB(0, 4, 0));
	DrawBlockTest(y++, RGB(0, 3, 0));
	DrawBlockTest(y++, RGB(0, 2, 0));
	DrawBlockTest(y++, RGB(0, 1, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 1));
	DrawBlockTest(y++, RGB(0, 0, 1));
	DrawBlockTest(y++, RGB(0, 0, 2));
	DrawBlockTest(y++, RGB(0, 0, 2));
	DrawBlockTest(y++, RGB(0, 0, 3));
	DrawBlockTest(y++, RGB(0, 0, 3));
	DrawBlockTest(y++, RGB(0, 0, 3));
	DrawBlockTest(y++, RGB(0, 0, 3));
	DrawBlockTest(y++, RGB(0, 0, 2));
	DrawBlockTest(y++, RGB(0, 0, 2));
	DrawBlockTest(y++, RGB(0, 0, 1));
	DrawBlockTest(y++, RGB(0, 0, 1));
	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(1, 1, 0));
	DrawBlockTest(y++, RGB(2, 2, 0));
	DrawBlockTest(y++, RGB(3, 3, 0));
	DrawBlockTest(y++, RGB(4, 4, 0));
	DrawBlockTest(y++, RGB(5, 5, 0));
	DrawBlockTest(y++, RGB(6, 6, 0));
	DrawBlockTest(y++, RGB(7, 7, 0));
	DrawBlockTest(y++, RGB(7, 7, 0));
	DrawBlockTest(y++, RGB(6, 6, 0));
	DrawBlockTest(y++, RGB(5, 5, 0));
	DrawBlockTest(y++, RGB(4, 4, 0));
	DrawBlockTest(y++, RGB(3, 3, 0));
	DrawBlockTest(y++, RGB(2, 2, 0));
	DrawBlockTest(y++, RGB(1, 1, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));

	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(1, 0, 0));
	DrawBlockTest(y++, RGB(2, 0, 1));
	DrawBlockTest(y++, RGB(3, 0, 1));
	DrawBlockTest(y++, RGB(4, 0, 2));
	DrawBlockTest(y++, RGB(5, 0, 2));
	DrawBlockTest(y++, RGB(6, 0, 3));
	DrawBlockTest(y++, RGB(7, 0, 3));
	DrawBlockTest(y++, RGB(7, 0, 3));
	DrawBlockTest(y++, RGB(6, 0, 3));
	DrawBlockTest(y++, RGB(5, 0, 2));
	DrawBlockTest(y++, RGB(4, 0, 2));
	DrawBlockTest(y++, RGB(3, 0, 1));
	DrawBlockTest(y++, RGB(2, 0, 1));
	DrawBlockTest(y++, RGB(1, 0, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));
	
	DrawBlockTest(y++, RGB(0, 0, 0));
	DrawBlockTest(y++, RGB(0, 1, 0));
	DrawBlockTest(y++, RGB(0, 2, 1));
	DrawBlockTest(y++, RGB(0, 3, 1));
	DrawBlockTest(y++, RGB(0, 4, 2));
	DrawBlockTest(y++, RGB(0, 5, 2));
	DrawBlockTest(y++, RGB(0, 6, 3));
	DrawBlockTest(y++, RGB(0, 7, 3));
	DrawBlockTest(y++, RGB(0, 7, 3));
	DrawBlockTest(y++, RGB(0, 6, 3));
	DrawBlockTest(y++, RGB(0, 5, 2));
	DrawBlockTest(y++, RGB(0, 4, 2));
	DrawBlockTest(y++, RGB(0, 3, 1));
	DrawBlockTest(y++, RGB(0, 2, 1));
	DrawBlockTest(y++, RGB(0, 1, 0));
	DrawBlockTest(y++, RGB(0, 0, 0));

	DrawBlockTest(y++, RGB(3, 3, 1));
	DrawBlockTest(y++, RGB(7, 7, 3));
}

