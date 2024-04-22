#ifndef __FONT_H__
#define __FONT_H__
#include "inttypes.h"


void InitFont(void);
void DrawFontText(int16_t x, int16_t y, char* sz, uint8_t uiColour);
void DrawFontChar(int16_t xp, int16_t yp, char c, uint8_t uiColour);


#endif // __FONT_H__

