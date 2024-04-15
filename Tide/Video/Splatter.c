#include "inttypes.h"
#include "Image.h"
#include "Random.h"
#include "Splatter.h"


void DrawSplatter(void)
{
	int16_t x;
	int16_t y;
	int16_t xr;
	int16_t yr;
	int16_t r;
	uint8_t uiColour;
	uint16_t uiRandomIndex;
	uint16_t i;
	uint8_t* pui;
	uint16_t uiWidth;
	uint16_t uiHeight;
	uint16_t uiRetries;
	int16_t* piRandom;
	uint16_t uiRandomLength;
	
	uiWidth = GetImageWidth();
	uiHeight = GetImageHeight();
	
	uiRandomLength = (uiWidth * uiHeight) / 35;
	if (uiRandomLength < 100)
	{
		uiRandomLength = 100;
	}
	uiRandomLength += rand() % 12;
	piRandom = AllocateRandomArray(uiRandomLength, 9, -5);
	
	pui = GetImageMemory();
	uiRetries = 10;
	uiRandomIndex = 0;
	for (y = 0; y < uiHeight; y++)
	{
		for (x = 0; x < uiWidth; x++)
		{
			uiColour = *(pui + (y * uiWidth) + x);
			for (i = 0; i < uiRetries; i++)
			{
				r = piRandom[uiRandomIndex];
				uiRandomIndex++;
				if (uiRandomIndex == uiRandomLength)
				{
					uiRandomIndex = 0;
				}
				
				xr = x + r;
				if ((xr >= 0) && (xr < uiWidth))
				{
					break;
				}
			}
			
			for (i = 0; i < uiRetries; i++)
			{
				r = piRandom[uiRandomIndex];
				uiRandomIndex++;
				if (uiRandomIndex == uiRandomLength)
				{
					uiRandomIndex = 0;
				}

				yr = y + r;
				if ((yr >= 0) && (yr < uiHeight))
				{
					break;
				}
			}
			
			*(pui + (yr * uiWidth) + xr) = uiColour;
		}
	}
	
	farfree(piRandom);
}

