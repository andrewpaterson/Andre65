#include "stdlib.h"
#include "stdbool.h"
#include "inttypes.h"
#include "Image.h"
#include "Heap.h"
#include "Splatter.h"
#include "Sprite.h"
#include "MemoryDump.h"
#include "Font.h"
#include "ItoA.h"
#include "SFTCommon.h"


extern uint8_t RGB(uint16_t r, uint16_t g, uint16_t b);
extern void BlockMove(void *pvDest, void* pvSource, size_t uiBytes);


void main(void)
{
	uint8_t*				puiData;
	uint8_t*				puiNext;
	uint16_t				uiType;
	uint16_t				i;
	uint16_t				uiCount;
	uint16_t				y;
	uint32_t				uiSkipToNext;
	struct SSFTContainer*	psContainer;
	struct SSFTImage*		psBackground;
	struct SSFTImage*		psStand;
	struct SSFTImage*		psWalk1;
	struct SSFTImage*		psWalk2;
	struct SSFTImage*		psWalk3;
	struct SSFTImage*		psWalk4;
	struct SSFTImage*		psWalk5;
	struct SSFTImage*		psWalk6;
	struct SSFTContained*	psHeader;
	char					sz[26];
	char*					psz;

	InitHeap((void*)0, (void*)0x0fffff, (void*)0x080000);

	SetImageParameters((void*)0x200000, 320, 200);

	puiData = (void*)0x030000;
	uiType = *((uint16_t*)puiData);
	uiSkipToNext = 0;

	y = 4;
	uiCount = 0xffff;
	
	if (uiType == SFT_TYPE_CONTAINER)
	{
		psContainer = (struct SSFTContainer*)puiData;
		uiCount = psContainer->uiCount;

		strcpy(sz, "CONTAINER (");
		i = strlen(sz);
		psz = &sz[i];
		
		psz = I16toA(uiCount, psz, 10);
		strcpy(psz, ")");

		DrawFontText(4, y, sz, 0xff);
		y += 8;

		puiData += sizeof(struct SSFTContainer);

		for (i = 0; i < uiCount; i++)
		{
			psHeader = (struct SSFTContained*)puiData;
			uiSkipToNext = psHeader->uiSkipToNext;				
			puiNext = (uint8_t*)((uint32_t)puiData + uiSkipToNext);
			
			puiData += sizeof(struct SSFTContained);
			uiType = *((uint16_t*)puiData);
			
			psz = I16toA(i, sz, 10);
			switch (uiType)
			{
				case SFT_TYPE_OPAQUE:
					strcpy(psz, ": Opaque Sprite");
					DrawFontText(4, y, sz, 0xff);
					y += 8;

					break;
				case SFT_TYPE_TRANSPARENT:
					strcpy(psz, ": Transparent Sprite");
					DrawFontText(4, y, sz, 0xff);
					y += 8;

					break;
				default:
					strcpy(psz, "<- UNKNOWN ->");
					DrawFontText(4, y, "<- UNKNOWN ->", 0xff);
					y += 8;
					uiCount = i + 1;
					break;
			}
			
			puiData = puiNext;
		}
	}
	
	
	
	for (;;)
	{
	}
    return;
}


void IRQHandler(void)
{
    return;
}

