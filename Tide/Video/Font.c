#include "stdlib.h"
#include "stdbool.h"
#include "Image.h"
#include "Font5x7.c"
#include "Font.h"


/* Generic to compute font bit on/off for this font */
// #define FONT_BIT(c, column, row) \
  // ((font_data[(c)+(column)] & 1<<(7-(row))) != 0)


void DrawFontChar(int16_t xp, int16_t yp, char c, uint8_t uiColour)
{
	uint8_t		uiColumn;
	uint16_t	x;
	uint16_t	y;
	bool		b;

	for (x = 0; x < 5; x++)
	{
		uiColumn = auiFont5x7Data[c * 5 + x];
		for (y = 0; y < 8; y++)
		{
			b = (uiColumn & (1 << (7 - y))) != 0;
			if (b)
			{
				DrawPixel(xp + x, yp + 7 - y, uiColour);
			}
		}
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

