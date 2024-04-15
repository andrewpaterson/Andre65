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

far uint8_t* guiVideoMemory;


struct SCircle
{
	int16_t x;
	int16_t y;
	int16_t r;
};


struct SGCircle
{
	struct SCircle	sCircle;
	int16_t 		xs;
	int16_t 		ys;
	uint16_t 		c;
};


void DrawBlockTest(uint16_t uiBlock, uint16_t uiColour)
{
    unsigned short xs;
	for (xs = uiBlock*2*320; xs < uiBlock*2*320 + 320*2; xs++)
	{
		*(guiVideoMemory + xs) = uiColour;
	}
}


extern unsigned char RGB(uint16_t r, uint16_t g, uint16_t b);


unsigned char RGBSlow(uint16_t r, uint16_t g, uint16_t b)
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
	psCircle->sCircle.x = x;
	psCircle->sCircle.y = y;
	psCircle->sCircle.r = r;
	psCircle->xs = xs;
	psCircle->ys = ys;
	psCircle->c = c;
}


void RandomiseScreen(far int16_t* piRandom, uint16_t uiLength)
{
	int16_t x;
	int16_t y;
	int16_t xr;
	int16_t yr;
	int16_t r;
	uint8_t uiColour;
	uint16_t uiRandomIndex;
	uint16_t i;
	
	uiRandomIndex = 0;
	for (y = 0; y < 200; y++)
	{
		for (x = 0; x < 320; x++)
		{
			uiColour = *(guiVideoMemory + (y * 320) + x);
			for (i = 0; i < 10; i++)
			{
				r = piRandom[uiRandomIndex];
				uiRandomIndex++;
				if (uiRandomIndex == uiLength)
				{
					uiRandomIndex = 0;
				}
				
				xr = x + r;
				if ((xr >= 0) && (xr < 320))
				{
					break;
				}
			}
			for (i = 0; i < 10; i++)
			{
				r = piRandom[uiRandomIndex];
				uiRandomIndex++;
				if (uiRandomIndex == uiLength)
				{
					uiRandomIndex = 0;
				}

				yr = y + r;
				if ((yr >= 0) && (yr < 200))
				{
					break;
				}
			}
			*(guiVideoMemory + (yr * 320) + xr) = uiColour;
		}
	}
}


void GenerateRandom(far int16_t* piRandom, uint16_t uiLength)
{
	uint16_t	i;
	int16_t		r;
	
	for (i = 0; i < uiLength; i++)
	{
		r = rand() % 7 - 3;
		piRandom[i] = 0;
	}
}


void main(void)
{
	uint8_t				t;
	unsigned int 		y;
	unsigned char 		c;
	far void*			pvBackground;
	far int16_t*		piRandom;
	unsigned char 		i;
	int16_t				r;
	uint16_t			uiRandomLength;
	
	struct SGCircle		asCircle[10];
	
	guiVideoMemory = (unsigned char*)0x200000;
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

	pvBackground = (far void*)0x220000;
	
	uiRandomLength = 1787;
	piRandom = farmalloc(uiRandomLength * sizeof(int16_t));  //farmalloc doesn't seem to be able to allocate more than 65KB total.
	//GenerateRandom(piRandom, uiRandomLength);
	for (y = 0; y < uiRandomLength; y++)
	{
		r = rand() % 7 - 3;
		piRandom[y] = r;
	}

	RandomiseScreen(piRandom, uiRandomLength);
	
	memcpy(pvBackground, guiVideoMemory, 64000);
	
	InitCircleStruct(&asCircle[0], 50, 60, 20, 2, 1, 0xff);
	InitCircleStruct(&asCircle[1], 110, 110, 30, -1, 3, RGB(7, 0, 3));
	InitCircleStruct(&asCircle[2], 240, 30, 25, 1, -2, RGB(1, 7, 1));
	InitCircleStruct(&asCircle[3], 202, 96, 10, 2, -2, RGB(2, 1, 3));
	InitCircleStruct(&asCircle[4], 253, 150, 35, -3, -1, RGB(5, 6, 0));
	InitCircleStruct(&asCircle[5], 253, 138, 12, 3, 2, RGB(6, 0, 1));
	InitCircleStruct(&asCircle[6], 50, 126, 32, 1, -1, RGB(4, 4, 3));
	InitCircleStruct(&asCircle[7], 157, 82, 25, -2, 1, RGB(3, 7, 0));
	InitCircleStruct(&asCircle[8], 145, 99, 26, -2, -3, RGB(4, 6, 1));
	InitCircleStruct(&asCircle[9], 52, 80, 31, 1, 1, RGB(5, 5, 1));
	
	SetImageParameters((void*)0x200000, 320, 200);

	y = 0;
	for (;;)
	{
		y++;
		if (y == 3)
		{
			memcpy((void*)guiVideoMemory, pvBackground, 64000);
			y = 0;
		}
		
		for (i = 0; i < 10; i++)
		{
			DrawCircleStruct(&asCircle[i]);
			MoveCircleStruct(&asCircle[i]);
		}
	}
	farfree(piRandom);
	farfree(pvBackground);
    return;
}


void IRQHandler(void)
{
    return;
}

