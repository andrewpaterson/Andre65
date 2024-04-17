#include "string.h"
#include "stdlib.h"
#include "inttypes.h"
#include "Image.h"
#include "Splatter.h"
#include "Circle.h"


struct SGCircle
{
	struct SCircle	sCircle;
	int16_t 		xs;
	int16_t 		ys;
	uint16_t 		c;
};


extern unsigned char RGB(uint16_t r, uint16_t g, uint16_t b);
extern unsigned char RGB(uint16_t r, uint16_t g, uint16_t b);
extern void BlockMove(void *pvDest, void* pvSource, size_t uiBytes);


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
	
	pasCircle = farmalloc(uiNumCircles * sizeof(struct SGCircle));
	
	for (i = 0; i < uiNumCircles; i++)
	{
		x = 50 + rand() % 220;
		y = 50 + rand() % 100;
		r = 2 + rand() % 5;
		xs = rand() % 6 -3;
		if (xs >= 0)
		{
			xs++;
		}
		ys = rand() % 6 -3;
		if (ys >= 0)
		{
			ys++;
		}
		rc = (rand() % 2 + 2) << 1;
		gc = (rand() % 2 + 2) << 1;
		bc = rand() % 2 + 2;
		InitCircleStruct(&pasCircle[i], x, y, r, xs, ys, RGB(rc, gc, bc));
	}
	return pasCircle;
}


void main(void)
{
	uint8_t				t;
	
	unsigned char 		c;
	void*				pvBackground;
	unsigned char 		i;
	int16_t				r;
	
	struct SGCircle*	pasCircle;
	uint16_t			uiNumCircles;
	uint16_t			y;
	
	SetImageParameters((void*)0x200000, 320, 200);
	DrawColourTest();

	pvBackground = (void*)0x220000;
	
	DrawSplatter();
	
	memcpy(pvBackground, (void*)GetImageMemory(), 64000);

	uiNumCircles = 40;
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
	farfree(pvBackground);
    return;
}


void IRQHandler(void)
{
    return;
}

