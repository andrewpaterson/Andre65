#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "inttypes.h"


void Test(void)
{
	bool		b;
	uint16_t	ui16x;
	uint16_t	ui16y;
	uint16_t	ui16z;
	uint16_t	ui16z0;

	int16_t		i16x;
	int16_t		i16y;
	int16_t		i16z;
	int16_t		i16z0;

	int32_t		i32x;
	int32_t		i32y;
	int32_t		i32z;
	int32_t		i32z0;
	
	ui16z0 = 0;
	for (ui16y = 0; ui16y < 0xffff; ui16y++)
	{
		for (ui16x = 0; ui16x < 0xffff; ui16x++)
		{
			ui16z = ui16x + ui16y;
			ui16z = ui16x - ui16y;
			ui16z0 += ui16z;
			b = ui16x < ui16y;
			b = ui16x > ui16z0;
		}
	}

	i16z0 = 0;
	for (i16y = -32768; i16y < 32767; i16y++)
	{
		for (i16x = -32768; i16x < 32767; i16x++)
		{
			i16z = i16x + i16y;
			i16z = i16x - i16y;
			i16z0 += i16z;
			b = i16x < i16y;
			b = i16x > i16z0;
		}
	}
	
	i32z0 = 0;
	for (i32y = -2147483648; i32y < 2147483647; i32y++)
	{
		for (i32x = -2147483648; i32x < 2147483647; i32x++)
		{
			i32z = i32x + i32y;
			i32z = i32x - i32y;
			i32z0 += i32z;
			b = i32x < i32y;
			b = i32x > i32z0;
		}
	}
}
