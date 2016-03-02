#include "safe_malloc.h"

void		*safe_malloc(size_t size)
{
	void	*res;

	if (!(res = malloc(size)))
	{
		ft_printf("%rMalloc fail\n");
		exit(1);
	}
	return (res);
}
