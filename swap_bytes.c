#include "swap_bytes.c"

int16_t			swap_int16(int16_t v)
{
	return ((v << 8) | ((v >> 8) & 0xFF));
}

int32_t			swap_int32(int32_t v)
{
	v = ((v << 8) & 0xFF00FF00) | ((v >> 8) & 0xFF00FF ); 
	return (v << 16) | ((v >> 16) & 0xFFFF);
}
