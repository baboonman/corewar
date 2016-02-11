#include "parse_arg.h"

static int	parse_dump(char **av, t_param *param)
{
	int		i;

	if (ft_strcmp(av[0], "-dump"))
		return (0);
	i = ft_strlen(av[1]);
	while (--i > 0)
	{
		if (!ft_isdigit(av[1][i]))
			return (-1);
	}
	param->is_dump = TRUE;
	param->nb_cycle_dump = ft_atoi(av[1]);
	return (2);
}

static void	print_param(t_param *param)
{
	if (param->is_dump)
	{
		ft_printf("Dump %d\n", param->nb_cycle_dump);
	}
}

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

static int	parse_player(t_param *param, int ac, char **av)
{
	int		i;
	int		nb_player;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			i++;
			if (i + 1 >= ac)
				return (FALSE);
			if ((nb_player = get_player_nb(av[i])) < 0)
				return (FALSE);
			i++;
		}
	}
}

int			parse_arg(t_param *param, int ac, char **av)
{
	int		idx;

	param->is_dump = FALSE;
	idx = 0;
	if (ac >= 2)
	{
		if ((idx = parse_dump(av, param)) < 0)
			return (FALSE);
	}
	parse_player(param, av + idx, argc - idx);
	print_param(param);
	return (TRUE);
}
