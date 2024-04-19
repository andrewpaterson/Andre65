#include "inttypes.h"
#include "Heap.h"


uint32_t guiRandom = 1;


uint32_t Random(void)
{
    guiRandom = guiRandom * 1103515243 + 12345;
    return (uint32_t)(guiRandom / 65536) % 32768;
}


void SeedRandom(uint32_t uiSeed)
{
    guiRandom = uiSeed;
}


int16_t* AllocateRandomArray(uint16_t uiRandomLength, uint16_t uiModulus, int16_t uiOffset)
{
	uint16_t	y;
	int16_t		r;
	int16_t*	piRandom;
	
	piRandom = Malloc(uiRandomLength * sizeof(int16_t));
	for (y = 0; y < uiRandomLength; y++)
	{
		r = (Random() % uiModulus) + uiOffset;
		piRandom[y] = r;
	}
	return piRandom;
}

