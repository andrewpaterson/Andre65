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
#include "Sprite.h"


extern uint8_t RGB(uint16_t r, uint16_t g, uint16_t b);
extern void BlockMove(void *pvDest, void* pvSource, size_t uiBytes);


void main(void)
{
	int16_t					y;
	uint16_t				uiCount;
	uint16_t				i;
	void*					pvData;
	struct SSpriteIterator 	sIter;
	char					sz[26];
	char*					psz;
	struct SSpriteHeader*	psSprite;
	struct SSpriteHeader*	psBackground;
	struct SSpriteHeader*	psMakiStand;
	struct SSpriteHeader*	psMakiWalk[6];

	InitHeap((void*)0, (void*)0x0fffff, (void*)0x080000);

	SetImageParameters((void*)0x200000, 320, 200);

	pvData = (void*)0x030000;

	
	y = 4;
	uiCount = StartSpritesIteration(pvData, &sIter);
	if (uiCount != 0)
	{
		strcpy(sz, "Container (");
		psz = &sz[strlen(sz)];
		psz = UI16toA(uiCount, psz, 10);
		strcpy(psz, ")");
		DrawFontText(4, y, sz, 0xff);
		y += 8;
		
		i = 0;
		for (;;)
		{
			psSprite = SpritesIterate(&sIter);
			if (psSprite == NULL)
			{
				break;
			}
			
			if (psSprite->uiType == SFT_TYPE_OPAQUE)
			{
				strcpy(sz, "Sprite (Opaque)");
				DrawFontText(4, y, sz, 0xff);
				y += 8;
			}
			else if (psSprite->uiType == SFT_TYPE_TRANSPARENT)
			{
				strcpy(sz, "Sprite (Transparent)");
				DrawFontText(4, y, sz, 0xff);
				y += 8;
			}
			
			if (i == 0)
			{
				psBackground = psSprite;
			}
			else if (i == 1)
			{
				psMakiStand = psSprite;
			}
			else if ((i >= 2) && (i <= 8))
			{
				psMakiWalk[i - 2] = psSprite;
			}
			
			i++;
		}
		
		DrawSprite(0, 0, psBackground);
		DrawSprite(70, 84, psMakiStand);

		strcpy(sz, "Done!");
		DrawFontText(4, y, sz, 0xff);
		y += 8;
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

