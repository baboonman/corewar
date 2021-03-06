/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_loop.h"

static int	is_alive(t_player *players, int nb_players, int nb)
{
	int		i;

	i = 0;
	while (i < nb_players)
	{
		if (players[i].nb == nb)
		{
			return (players[i].is_alive);
		}
		i++;
	}
	return (FALSE);
}

static int	execute_player_process(t_vm *vm)
{
	t_list		*process;
	t_process	*proc;

	process = vm->lst_process;
	while (process)
	{
		proc = (t_process *)process->content;
		if (is_alive(vm->players, vm->nb_players, proc->player_nb))
		{
			if (vm->param.verbose)
				ft_printf("Execute process: %d, %d\n", proc->player_nb,
						proc->number_cycles);
			execute_process(process->content, vm);
		}
		process = process->next;
	}
	return (TRUE);
}

int			execute_loop(t_vm *vm)
{
	execute_player_process(vm);
	return (check_live(vm));
}
