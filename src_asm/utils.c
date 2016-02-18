#include "utils.h"

static int	test(char c)
{
	return (c == ' ' || c == '\t');
}

char		*ft_strchr_space(char *s)
{
	while (*s != '\0' && !test(*s))
		s++;
	if (*s == '\0')
		return (NULL);
	return (s);
}

void		*safe_malloc(size_t size)
{
	void	*res;

	if (!(res = malloc(size)))
	{
		ft_printf("malloc fail\n");
		exit(1);
	}
	return (res);
}
