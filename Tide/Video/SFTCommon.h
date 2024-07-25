#ifndef __SFT_COMMON_H__
#define __SFT_COMMON_H__
#include "inttypes.h"


#define SFT_TYPE_OPAQUE			(uint16_t)0xe457
#define SFT_TYPE_TRANSPARENT	(uint16_t)0xe4f9
#define SFT_TYPE_CONTAINER		(uint16_t)0xe4ef


struct SSFTImage
{
	uint16_t	uiType;
	uint16_t	uiImageWidth;
	uint16_t	uiImageHeight;
};


struct SSFTCelRun
{
	uint16_t	uiFlags;  //0x8000: Start of run flag.  //0x7fff: run skip mask.  or how many pixels to add before the current run starts drawing
	uint16_t	uiRunLength;
};


struct SSFTContainer
{
	uint16_t	uiType;
	uint16_t	uiCount;  //Count of contained images.
};


struct SSFTContained
{
	uint16_t	uiSkipToNext;  //How many bytes to seek forward to the next contained (or zero if no more images contained).  Relative to the end of this struct.
};  //end of struct == start of SSFT image type.


#endif // __SFT_COMMON_H__

