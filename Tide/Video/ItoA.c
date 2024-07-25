#include "itoa.h"


void Reverse(char* str, uint16_t length)
{
    uint16_t 	start;
    uint16_t 	end;
	char 		temp;

    start = 0;
    end = length - 1;
	
    while (start < end) 
	{
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}


char* I16toA(int16_t num, char* str, uint16_t base)
{
    uint16_t	i;
    bool 		isNegative;
	int16_t 	rem;

    i = 0;
    isNegative = false;
 
    if (num == 0) 
	{
        str[i++] = '0';
        str[i] = '\0';
        return &str[i];
    }
 
    if ((num < 0) && (base == 10))
	{
        isNegative = true;
        num = -num;
    }
 
    while (num != 0) 
	{
        rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    if (isNegative)
	{
        str[i++] = '-';
	}
 
    str[i] = '\0';
 
    Reverse(str, i);
 
    return &str[i];
}


char* I32toA(int32_t num, char* str, uint32_t base)
{
    uint16_t	i;
    bool 		isNegative;
	int32_t 	rem;

    i = 0;
    isNegative = false;
 
    if (num == 0) 
	{
        str[i++] = '0';
        str[i] = '\0';
        return &str[i];
    }
 
    if ((num < 0) && (base == 10))
	{
        isNegative = true;
        num = -num;
    }
 
    while (num != 0) 
	{
        rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    if (isNegative)
	{
        str[i++] = '-';
	}
 
    str[i] = '\0';
 
    Reverse(str, i);
 
    return &str[i];
}

