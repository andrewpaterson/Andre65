#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "inttypes.h"


struct SCircle
{
	int16_t x;
	int16_t y;
	int16_t r;
};


void InitCircle(struct SCircle* psCircle, int16_t x, int16_t y, int16_t r);
void DrawCircle(int16_t xc, int16_t yc, int16_t r, uint8_t uiColour);


#endif // __CIRCLE_H__

