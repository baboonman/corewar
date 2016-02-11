#include "swap_bytes.h"

int16_t			swap_int16(int16_t v)
{
	return ((v << 8) | ((v >> 8) & 0xFF));
}

int32_t			swap_int32(int32_t v)
{
	v = ((v << 8) & 0xFF00FF00) | ((v >> 8) & 0xFF00FF ); 
	return (v << 16) | ((v >> 16) & 0xFFFF);
}

uint16_t		swap_uint16(uint16_t v) 
{
    return ((v << 8) | (v >> 8));
}

uint32_t		swap_uint32(uint32_t v)
{
    v = ((v << 8) & 0xFF00FF00 ) | ((v >> 8) & 0xFF00FF ); 
    return ((v << 16) | (v >> 16));
}

int					swap_nbytes(int v, int nbB)
{
	if (nbB == 2)
		return (swap_uint16(v));
	if (nbB == 4)
		return (swap_uint32(v));
//	ft_printf("nb of bytes to swap not supported\n");
	return v;
}
