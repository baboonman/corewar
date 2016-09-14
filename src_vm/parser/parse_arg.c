/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	print_param(t_param *p)
{
	int		i;

	if (p->is_dump)
		ft_printf("Dump %d\n", p->nb_cycle_dump);
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

static int	process_loop_parse_first_arg(char **av, int ac, int i,
		t_param *param)
{
	int		ret;

	if ((ret = parse_dump(av + i, param, ac - i)) < 0)
		return (-1);
	else if (ret > 0)
		return (ret + 1);
	if (parse_verbose(av + i, param))
		return (1);
	if (parse_ncurses(av + i, param))
		return (1);
	return (-2);
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
		ret = process_loop_parse_first_arg(av, ac, i, param);
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			break ;
		i += ret;
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
