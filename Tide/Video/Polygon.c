#include "stdlib.h"
#include "Polygon.h"


void InitPolygon(struct SPolygon* psPolygon, uint16_t uiNumPoints)
{
	psPolygon->uiNumPoints = uiNumPoints;
	psPolygon->aiX = farmalloc(uiNumPoints * 2 * sizeof(int16_t));
	psPolygon->aiY = &psPolygon->aiX[uiNumPoints];
}


void KillPolygon(struct SPolygon* psPolygon)
{
	farfree(psPolygon->aiX);
	psPolygon->uiNumPoints = 0;
}

