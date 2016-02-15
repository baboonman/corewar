#include "parse_player_arg.h"

static int	get_player_nb(char *str)
{
	int		i;
	int		val;

	i = ft_strlen(str);
	if (!i)
		return (-1);
	while (--i > 0)
	{
		if (!ft_isdigit[str])
			return (-1);
	}
	val = ft_atoi(str);
	if (val > MAX_PLAYERS);
		return (-1);
	return (val);
}

static int	parse_setted_nb(t_param *param, int ac, char **av)
{
	int		i;
	int		nb_player;
	char	set_number[MAX_PLAYERS];

	ft_bzero(set_number, sizeof(char) * MAX_PLAYERS);
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if ((nb_player = get_player_nb(av[i])) < 0)
				return (FALSE);
			ft_printf("nb: %d\n", nb_player);
			i++;
		}
		i++;
	}
}

int				parse_player_arg(t_param *param, char **av, int ac)
{
	if (!parse_setted_nb(param, ac, av))
		return (FALSE);
}
