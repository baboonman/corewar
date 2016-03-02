#include "get_hexa.h"

static char	get_char(char val)
{
	char binding[6];

	binding[0] = 'a';
	binding[1] = 'b';
	binding[2] = 'c';
	binding[3] = 'd';
	binding[4] = 'e';
	binding[5] = 'f';
	if (val < 10)
		return (val + '0');
	if (val > 15)
		return ('Z');
	return (binding[val - 10]);
}

int			get_hexa(uint8_t val, char *out)
{
	out[1] = get_char(val % 16);
	out[0] = get_char(val / 16);
	return (TRUE);
}

static int	calc_i(uint64_t n)
{
	int		i;

	i = 0;
	while (n > 15)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static char	*get_str(void)
{
	char	*str;
	int		i;

	if (!(str = ft_strnew(8)))
		return (NULL);
	i = 0;
	while (i < 8)
	{
		str[i] = '0';
		i++;
	}
	return (str);
}

char		*get_hexa_32(uint32_t val)
{
	char	tmp;
	int		i;
	int		n;
	char	*res;

	i = calc_i(val);
	if (i > 8)
		return (NULL);
	if (!(res = get_str()))
		return (NULL);
	n = 7 - i;
	while (i >= 0)
	{
		tmp = val % 16;
		res[i + n] = get_char(tmp);
		val /= 16;
		i--;
	}
	return (res);
}
