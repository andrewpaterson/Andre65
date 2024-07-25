#ifndef __MEMORY_DUMP_H__
#define __MEMORY_DUMP_H__
#include "inttypes.h"


void toByteHex(char* sz, uint8_t uiByte);
void toQuadHex(char* sz, void* pvMem);
void DumpMemory(void* pvMem, uint16_t x, uint16_t y, uint16_t uiCount, uint8_t uiColour);


#endif // __MEMORY_DUMP_H__

