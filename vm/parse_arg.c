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
	print_param(param);
	return (TRUE);
}
