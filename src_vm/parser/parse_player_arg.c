/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (!ft_isdigit(*str))
			return (-1);
	}
	val = ft_atoi(str);
	if (val > MAX_PLAYERS)
		return (-1);
	return (val);
}

static int	get_next_free_nb(int *set_number, int cur_player)
{
	int		i;
	int		min;

	i = 0;
	min = 1;
	while (i < MAX_PLAYERS)
	{
		if (set_number[i] == min)
		{
			++min;
			i = 0;
		}
		else
			++i;
	}
	set_number[cur_player] = min;
	return (min);
}

static int	get_players_file(int *set_number, t_param *p, int ac, char **av)
{
	int		i;
	int		cur_player;

	i = 0;
	cur_player = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if ((i += 2) >= ac)
				return (FALSE);
			p->player_nb[cur_player] = set_number[cur_player];
		}
		else
			p->player_nb[cur_player] = get_next_free_nb(set_number, cur_player);
		if (p->file_players[p->player_nb[cur_player] - 1])
			return (FALSE);
		p->file_players[p->player_nb[cur_player] - 1] = av[i];
		++cur_player;
		++i;
	}
	return (TRUE);
}

static int	parse_setted_nb(t_param *p, int ac, char **av)
{
	int		i;
	int		nb_player;
	int		set_number[MAX_PLAYERS];

	ft_bzero(set_number, sizeof(int) * MAX_PLAYERS);
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			if (++i >= ac)
				return (FALSE);
			if ((nb_player = get_player_nb(av[i])) < 0
					|| nb_player > MAX_PLAYERS)
				return (FALSE);
			set_number[p->nb_players] = nb_player;
			++i;
		}
		++(p->nb_players);
		i++;
	}
	if (!get_players_file(set_number, p, ac, av))
		return (FALSE);
	return (p->nb_players <= MAX_PLAYERS);
}

int			parse_player_arg(t_param *param, char **av, int ac)
{
	if (!parse_setted_nb(param, ac, av))
		return (FALSE);
	return (check_ext(param));
}
