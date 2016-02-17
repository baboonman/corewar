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
	return (1);
}

static int	parse_verbose(char **av, t_param *param)
{
	if (ft_strcmp(av[0], "-v"))
		return (-1);
	param->verbose = TRUE;
	return (0);
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
				i,
				p->file_players[i]);
		++i;
	}
}

int			parse_arg(t_param *param, int ac, char **av)
{
	int		idx;
	int		i;

	param->is_dump = FALSE;
	idx = 0;
	i = 0;
/*	while (i < ac)
	{
		if ((idx = parse_dump(av + i, param)) < 0)
			return (FALSE);
		idx += i;
		i = idx + 1;
	}*///TODO clean this up bitch
	if (!parse_player_arg(param, av + i, ac - idx))
		return (FALSE);
	print_param(param);
	return (TRUE);
}
