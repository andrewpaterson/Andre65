#include "string.h"
#include "stdlib.h"
#include "Circle.h"


void main(void)
{
    unsigned short xs;
    for (;;)
    {
        for (xs = 0; xs < 64000; xs++)
        {
            pokeb((unsigned int)(0x200000 + xs), 0x00);
        }
        for (xs = 0; xs < 64000; xs++)
        {
            pokeb((unsigned int)(0x200000 + xs), 0xff);
        }
    }
    return;
}


void IRQHandler(void)
{
    return;
}

