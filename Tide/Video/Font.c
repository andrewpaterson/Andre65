#include "stdlib.h"
#include "stdbool.h"
#include "Image.h"
#include "Font5x7.h"
#include "Font.h"


void DrawFontCharClipped(int16_t xp, int16_t yp, char c, uint8_t uiColour)
{
	uint8_t		uiRow;
	uint16_t	x;
	uint16_t	y;
	bool		b;
	uint16_t	uiCTimes7;

	c-=32;
	uiCTimes7 = c << 3;
	for (y = 0; y < 7; y++)
	{
		uiRow = gauiFont5x7Data[uiCTimes7 + y];
		for (x = 0; x < 5; x++)
		{
			b = (uiRow & (1 << (4-x))) != 0;
			if (b)
			{
				DrawPixel(xp + x, yp + y, uiColour);
			}
		}
	}
}

void DrawFontChar(int16_t xp, int16_t yp, char c, uint8_t uiColour)
{
	uint8_t*	puiVideoMemory;
	uint16_t	uiWidth;

	uiWidth = GetImageWidth();
	if ((xp + 5 < 0) ||
		(xp >= (int16_t)uiWidth) || 
		(yp + 8 < 0) ||
		(yp >= (int16_t)GetImageHeight()))
	{
		return;
	}
	
	if ((xp  < 0) ||
		(xp >= (int16_t)uiWidth - 5) || 
		(yp  < 0) ||
		(yp >= (int16_t)GetImageHeight() - 8))
	{
		DrawFontCharClipped(xp, yp, c, uiColour);
		return;
	}
	
	
	puiVideoMemory = GetImageMemory() + yp * uiWidth + xp;
	DrawFontCharUnsafeASM(puiVideoMemory, uiWidth, c, uiColour);
}


void DrawFontText(int16_t x, int16_t y, char* sz, uint8_t uiColour)
{
	char c;
	
	c = *sz;
	while (c != 0)
	{
		DrawFontChar(x, y, c, uiColour);
		c = *(++sz);
		x += 6;
	}
}

