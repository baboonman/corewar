#include "parse_arg.h"

static int	parse_dump(char **av, t_param *param, int ac)
{
	int		i;

	if (ac < 2)
		return (0);
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
	return (1);
}

static int	parse_verbose(char **av, t_param *param)
{
	if (ft_strcmp(av[0], "-v"))
		return (FALSE);
	param->verbose = TRUE;
	return (TRUE);
}

static void	print_param(t_param *p)
{
	int		i;

	if (p->is_dump)
	{
		ft_printf("Dump %d\n", p->nb_cycle_dump);
	}
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (p->file_players[i])
			ft_printf("nb: %d, file: %s\n",
				i + 1,
				p->file_players[i]);
		++i;
	}
}

static int	parse_first_arg(t_param *param, int ac, char **av)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	param->is_dump = FALSE;
	param->verbose = FALSE;
	while (i < ac)
	{
		if ((ret = parse_dump(av + i, param, ac - i)) < 0)
			return (-1);
		else if (ret > 0)
		{
			i += ret + 1;
			continue ;
		}
		if (parse_verbose(av + i, param))
		{
			++i;
			continue ;
		}
		break ;
	}
	return (i);
}

int			parse_arg(t_param *param, int ac, char **av)
{
	int		pos;

	if ((pos = parse_first_arg(param, ac, av)) < 0)
		return (FALSE);
	if (!parse_player_arg(param, av + pos, ac - pos))
		return (FALSE);
	if (param->verbose)
		print_param(param);
	return (TRUE);
}
