#ifndef __RANDOM_H__
#define __RANDOM_H__
#include "inttypes.h"


uint32_t Random(void);
void SeedRandom(uint32_t uiSeed);
int16_t* AllocateRandomArray(uint16_t uiRandomLength, uint16_t uiModulus, int16_t uiOffset);


#endif // __RANDOM_H__

