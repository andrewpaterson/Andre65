#include "stdlib.h"
#include "Heap.h"


extern void* _END_UDATA;


struct SAllocation
{
	void* 		pvNextAllocation;
	uint32_t	uiSize;
};


 void* gpvStartOfRAM;
 void* gpvEndOfRAM;
 
 void* gpvStartOfHeap;
 void* gpvCurrentHeap;
 

void InitHeap(void* pvStartOfRAM, void* pvEndOfRAM)
{
	gpvStartOfRAM = pvStartOfRAM;
	gpvEndOfRAM = pvEndOfRAM;
	gpvStartOfHeap = _END_UDATA;
	gpvCurrentHeap = NULL;
}


void* Malloc(uint16_t uiSize)
{
	uint32_t				uiNext;
	void*					pvCurrent;
	struct SAllocation*		ps;
	
	uiSize += sizeof(struct SAllocation);
	if (gpvCurrentHeap == NULL)
	{
		uiNext = (uint32_t)gpvStartOfHeap;
		gpvCurrentHeap = gpvStartOfHeap;

		ps = (struct SAllocation*)gpvCurrentHeap;
		ps->pvNextAllocation = NULL;
		ps->uiSize = uiSize;

		return (void*)((uint32_t)uiNext + sizeof(struct SAllocation));
	}
	else
	{
		uiNext = (uint32_t)gpvCurrentHeap;
		pvCurrent = gpvCurrentHeap;
		gpvCurrentHeap = (void*)(uiNext + uiSize);

		ps = (struct SAllocation*)gpvCurrentHeap;
		ps->pvNextAllocation = NULL;
		ps->uiSize = uiSize;
		
		ps = (struct SAllocation*)gpvCurrentHeap;
		ps->pvNextAllocation = NULL;

		return (void*)((uint32_t)uiNext + sizeof(struct SAllocation));
	}
}


void Free(void* pv)
{
}

