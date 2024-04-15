#include "stdlib.h"
#include "Splatter.h"


int16_t* GenerateRandom(uint16_t uiRandomLength)
{
	uint16_t			y;
	uint16_t			r;
	uint16_t			x;
	uint16_t*			piRandom;
	
	piRandom = farmalloc(uiRandomLength * sizeof(int16_t));  //farmalloc doesn't seem to be able to allocate more than 65KB total.
	for (y = 0; y < uiRandomLength; y++)
	{
		x = rand();
		r = x % 7 - 3;
		piRandom[y] = r;
	}
	return (int16_t*)piRandom;
}

