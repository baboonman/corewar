#include "parser.h"

int64_t				ft_pow(int64_t x, int n)
{
	int64_t			y;

	y = 1;
	while (n)
	{
		y *= x;
		n--;
	}
	return (y);
}

int					check_overflow(int64_t v, int nb_bytes, int cur_line,
									t_error **err)
{
	int64_t			lim;

	lim = ft_pow(256, nb_bytes) / 2;
	if (v >= lim - 1 || v < -1 * lim)
	{
		*err = get_error(OVERFLOW);
		(*err)->line = cur_line;
		return (FALSE);
	}
	return (TRUE);
}

size_t				ft_memcat(void *dest, void *src, size_t i, size_t n)
{
	ft_memcpy(dest + i, src, n);
	i += n;
	return (i);
}
