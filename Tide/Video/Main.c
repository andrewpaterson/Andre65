#include "stdlib.h"
#include "stdbool.h"
#include "inttypes.h"
#include "Image.h"
#include "Heap.h"
#include "Splatter.h"
#include "Circle.h"
#include "Font.h"


struct SGCircle
{
	struct SCircle	sCircle;
	int16_t 		xs;
	int16_t 		ys;
	uint16_t 		c;
};


extern uint8_t RGB(uint16_t r, uint16_t g, uint16_t b);
extern void BlockMove(void *pvDest, void* pvSource, size_t uiBytes);


uint8_t RGBSlow(uint16_t r, uint16_t g, uint16_t b)
{
	return (r & 0x7) | ((g & 0x7) << 3) | ((b & 0x3) << 6);
}


void DrawCircleStruct(struct SGCircle* psCircle)
{
	DrawCircle(psCircle->sCircle.x, psCircle->sCircle.y, psCircle->sCircle.r, psCircle->c);
}


void MoveCircleStruct(struct SGCircle* psCircle)
{
	psCircle->sCircle.x += psCircle->xs;
	psCircle->sCircle.y += psCircle->ys;
	if (psCircle->sCircle.x - psCircle->sCircle.r < 0)
	{
		psCircle->sCircle.x = psCircle->sCircle.r;
		psCircle->xs = -psCircle->xs;
	}
	if (psCircle->sCircle.x + psCircle->sCircle.r > 319)
	{
		psCircle->sCircle.x = 319 - psCircle->sCircle.r;
		psCircle->xs = -psCircle->xs;
	}
	if (psCircle->sCircle.y - psCircle->sCircle.r < 0)
	{
		psCircle->sCircle.y = psCircle->sCircle.r;
		psCircle->ys = -psCircle->ys;
	}
	if (psCircle->sCircle.y + psCircle->sCircle.r > 199)
	{
		psCircle->sCircle.y = 199 - psCircle->sCircle.r;
		psCircle->ys = -psCircle->ys;
	}
}


void InitCircleStruct(struct SGCircle* psCircle, int16_t x, int16_t y, int16_t r, int16_t xs, int16_t ys, uint16_t c)
{
	InitCircle(&psCircle->sCircle, x, y, r);
	psCircle->xs = xs;
	psCircle->ys = ys;
	psCircle->c = c;
}


struct SGCircle* InitCircles(uint16_t uiNumCircles)
{
	uint16_t	i;
	int16_t		x;
	int16_t		y;
	int16_t		r;
	int16_t		xs;
	int16_t		ys;
	uint16_t	rc;
	uint16_t	gc;
	uint16_t	bc;
	struct SGCircle* pasCircle;

	pasCircle = Malloc(uiNumCircles * sizeof(struct SGCircle));
	
	for (i = 0; i < uiNumCircles; i++)
	{
		x = 50 + Random() % 220;
		y = 50 + Random() % 100;
		r = 2 + Random() % 5;
		xs = Random() % 6 -3;
		if (xs >= 0)
		{
			xs++;
		}
		ys = Random() % 6 -3;
		if (ys >= 0)
		{
			ys++;
		}
		rc = (Random() % 2 + 2) << 1;
		gc = (Random() % 2 + 2) << 1;
		bc = Random() % 2 + 2;
		InitCircleStruct(&pasCircle[i], x, y, r, xs, ys, RGB(rc, gc, bc));
	}
	return pasCircle;
}


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


void main(void)
{
	uint8_t				t;
	
	uint8_t 			c;
	void*				pvBackground;
	uint8_t 			i;
	int16_t				r;
	
	struct SGCircle*	pasCircle;
	uint16_t			uiNumCircles;
	uint16_t			y;
	

	InitHeap((void*)0, (void*)0x0fffff, (void*)0x080000);

	SetImageParameters((void*)0x200000, 320, 200);

	DrawColourTest();

	pvBackground = (void*)0x220000;
	
	DumpMemory((void*)0x020000, 2, 24, 64, 0xff);

	for (;;)
	{
	}
	
	memcpy(pvBackground, (void*)GetImageMemory(), 64000);

	uiNumCircles = 3;
	pasCircle = InitCircles(uiNumCircles);
	
	for (;;)
	{
		SetImageParameters((void*)0x200000, 320, 200);
		BlockMove((void*)0x200000, (void*)0x220000, 63999);

		for (i = 0; i < uiNumCircles; i++)
		{
			DrawCircleStruct(&pasCircle[i]);
			MoveCircleStruct(&pasCircle[i]);
		}

		*((uint8_t*)0x280000) = 0;
		SetImageParameters((void*)0x210000, 320, 200);
		BlockMove((void*)0x210000, (void*)0x220000, 63999);

		for (i = 0; i < uiNumCircles; i++)
		{
			DrawCircleStruct(&pasCircle[i]);
			MoveCircleStruct(&pasCircle[i]);
		}
		
		*((uint8_t*)0x280000) = 1;
	}

    return;
}


void IRQHandler(void)
{
    return;
}

