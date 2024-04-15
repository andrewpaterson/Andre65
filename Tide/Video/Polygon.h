#ifndef __POLYGON_H__
#define __POLYGON_H__
#include "inttypes.h"


struct SPolygon
{
	uint16_t	uiNumPoints;
	int16_t*	aiX;
	int16_t*	aiY;
};


void InitPolygon(struct SPolygon* psPolygon, uint16_t uiNumPoints);


#endif // __POLYGON_H__

