#include "stdlib.h"
#include "stdbool.h"
#include "Image.h"
#include "Font5x7.c"
#include "Font.h"


/* Generic to compute font bit on/off for this font */
// #define FONT_BIT(c, column, row) \
  // ((font_data[(c)+(column)] & 1<<(7-(row))) != 0)


void DrawFontCharClipped(int16_t xp, int16_t yp, char c, uint8_t uiColour)
{
	uint8_t		uiColumn;
	uint16_t	x;
	uint16_t	y;
	bool		b;
	uint16_t	uiCTimes5;

	uiCTimes5 = (c << 2) + c;
	for (x = 0; x < 5; x++)
	{
		uiColumn = auiFont5x7Data[uiCTimes5 + x];
		for (y = 0; y < 8; y++)
		{
			b = (uiColumn & (1 << y)) != 0;
			if (b)
			{
				DrawPixel(xp + x, yp + y, uiColour);
			}
		}
	}
}


void DrawFontChar(int16_t xp, int16_t yp, char c, uint8_t uiColour)
{
	uint8_t		uiColumn;
	uint16_t	x;
	uint16_t	y;
	bool		b;
	uint16_t	uiCTimes5;
	uint8_t*	puiVideoMemory;
	uint8_t*	puiStartOfColumn;
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
	uiCTimes5 = (c << 2) + c;
	puiStartOfColumn = puiVideoMemory;
	for (x = 0; x < 5; x++)
	{
		uiColumn = auiFont5x7Data[uiCTimes5 + x];
		for (y = 0; y < 8; y++)
		{
			b = (uiColumn & (1 << y)) != 0;
			if (b)
			{
				*puiVideoMemory = uiColour;
				//DrawPixel(xp + x, yp + 7 - y, uiColour);
			}
			puiVideoMemory += uiWidth;
		}
		puiStartOfColumn++;
		puiVideoMemory = puiStartOfColumn;
	}
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

