#ifndef __HEAP_H__
#define __HEAP_H__
#include "inttypes.h"


void InitHeap(void* pvStartOfRAM, void* pvEndOfRAM);
void* Malloc(uint16_t);
void Free(void* pv);


#endif // __HEAP_H__

