#include "stdlib.h"
#include "stdbool.h"
#include "Font.h"
#include "MemoryDump.h"


void toByteHex(char* sz, uint8_t uiByte)
{
	uint8_t	uiHi;
	uint8_t	uiLo;
	char 	c;
	
	uiHi = uiByte >> 4;
	uiLo = uiByte & 0xf;
	c = uiHi < 10 ? '0' + uiHi : 'A' + uiHi - 10;
	sz[0] = c;
	c = uiLo < 10 ? '0' + uiLo : 'A' + uiLo - 10;
	sz[1] = c;
	sz[2] = ' ';
	sz[3] = 0;
}


void toQuadHex(char* sz, void* pvMem)
{
	uint8_t*	puiMem;
	
	puiMem = pvMem;
	toByteHex(sz, *puiMem);
	sz+=3;
	puiMem++;
	toByteHex(sz, *puiMem);
	sz+=3;
	puiMem++;
	toByteHex(sz, *puiMem);
	sz+=3;
	puiMem++;
	toByteHex(sz, *puiMem);
}


void DumpMemory(void* pvMem, uint16_t x, uint16_t y, uint16_t uiCount, uint8_t uiColour)
{
	uint16_t 	i;
	uint8_t*	puiMem;
	char		szBuffer[64];
	char*		sz;
	uint16_t	uiLength;
	uint16_t	uiColumn;
	uint16_t	uiRow;
	bool		bDrawn;
	
	puiMem = pvMem;
	uiColumn = 0;
	uiRow = 0;
	sz = szBuffer;
	for (i = 0 ; i < uiCount; i++)
	{
		toQuadHex(sz, puiMem);
		bDrawn = false;
		puiMem += 4;
		uiColumn++;
		
		if (uiColumn == 4)
		{
			DrawFontText(x, y, szBuffer, uiColour);
			bDrawn = true;
			
			sz = szBuffer;
			uiColumn = 0;
			y += 8;
			uiRow++;
			if (uiRow == 4)
			{
				y += 8;
				uiRow = 0;
			}
		}
		else
		{
			strcat(sz, ": ");
			sz += strlen(sz);
		}
	}
	
	if (!bDrawn)
	{
		DrawFontText(x, y, sz, uiColour);
	}
}

