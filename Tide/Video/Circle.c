#include "stdlib.h"
#include "Image.h"
#include "Circle.h"


void InitCircle(struct SCircle* psCircle, int16_t x, int16_t y, int16_t r)
{
	psCircle->x = x;
	psCircle->y = y;
	psCircle->r = r;
}


void DrawCircleEigths(int16_t xc, int16_t yc, int16_t x, int16_t y, uint8_t uiColour)
{
	DrawPixel(xc + x, yc + y, uiColour);
	DrawPixel(xc - x, yc + y, uiColour);
	DrawPixel(xc + x, yc - y, uiColour);
	DrawPixel(xc - x, yc - y, uiColour);
	DrawPixel(xc + y, yc + x, uiColour);
	DrawPixel(xc - y, yc + x, uiColour);
	DrawPixel(xc + y, yc - x, uiColour);
	DrawPixel(xc - y, yc - x, uiColour);
}


void DrawCircle(int16_t xc, int16_t yc, int16_t r, uint8_t uiColour) 
{
	int16_t x = 0;
	int16_t y = r;
	int16_t p = 1 - r;

	DrawCircleEigths(xc, yc, x, y, uiColour);
	while (x < y) 
	{
		x++;
		if (p < 0)
		{
			p += 2 * x + 1;
		}
		else 
		{
			y--;
			p += 2 * (x - y) + 1;
		}
		DrawCircleEigths(xc, yc, x, y, uiColour);
	}
}

