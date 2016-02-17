#include "libft.h"

static char	*ft_del_space(const char *str)
{
	while (*str != '\0' && (*str == ' ' || *str == '\t' || *str == '\v'
				|| *str == '\n' || *str == '\r' || *str == '\f'))
	{
		str++;
	}
	return ((char *)str);
}

int64_t		ft_atoli(const char *str)
{
	int64_t		result;
	int64_t		neg;
	char		*str2;

	result = 0;
	str2 = ft_del_space(str);
	neg = 1;
	if (str2[0] == '-')
	{
		neg = -1;
		str2++;
	}
	else if (str2[0] == '+')
		str2++;
	while (*str2 >= '0' && *str2 <= '9')
	{
		result *= 10;
		result += (*str2++ - '0') * neg;
	}
	return (result);
}
