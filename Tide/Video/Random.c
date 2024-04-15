#include "stdlib.h"
#include "inttypes.h"


int16_t* AllocateRandomArray(uint16_t uiRandomLength, uint16_t uiModulus, int16_t uiOffset)
{
	uint16_t	y;
	int16_t		r;
	int16_t*	piRandom;
	
	piRandom = farmalloc(uiRandomLength * sizeof(int16_t));  //farmalloc doesn't seem to be able to allocate more than 64KB total.
	for (y = 0; y < uiRandomLength; y++)
	{
		r = (rand() % uiModulus) + uiOffset;
		piRandom[y] = r;
	}
	return piRandom;
}

