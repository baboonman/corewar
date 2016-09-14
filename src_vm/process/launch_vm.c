/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_vm.h"

static int	sub_time(t_loop_param *p)
{
	unsigned long int	t1;
	unsigned long int	t2;
	unsigned long int	t3;

	t1 = p->a.tv_sec * 1000000 + p->a.tv_usec;
	t2 = p->b.tv_sec * 1000000 + p->b.tv_usec;
	t3 = (unsigned long int)((1.0f / p->input.tps) * 1000000.0f);
	if (t2 - t1 > t3)
		return (1);
	return (0);
}

static void	ncurses_render(t_vm *vm)
{
	if (vm->param.is_ncurses)
	{
		update_player_info(vm);
		update_vm_info(vm);
		update_ins_info(vm);
		update_panels();
		doupdate();
	}
}

static int	run_lap(t_vm *vm, t_loop_param *p, int *i, int *flag)
{
	get_input(&(p->input));
	gettimeofday(&(p->b), NULL);
	if (!vm->param.is_ncurses || (p->input.pause > 0 && sub_time(p)))
	{
		vm->tot_cycle = *i;
		vm->fps = p->input.tps;
		if (!execute_loop(vm))
		{
			if (vm->param.verbose)
				ft_printf("Total number of loop: %d\n", *i);
			return (FALSE);
		}
		refresh_mem_display(vm);
		gettimeofday(&(p->a), NULL);
		++(*i);
	}
	if (vm->param.is_dump && vm->param.nb_cycle_dump <= *i)
	{
		*flag = 1;
		dump_memory(vm);
		return (FALSE);
	}
	return (TRUE);
}

int			launch_vm(t_vm *vm)
{
	int				i;
	int				flag;
	t_loop_param	p;

	init_launch_vm(vm, &p, &i, &flag);
	while (1)
	{
		if (!run_lap(vm, &p, &i, &flag))
			break ;
		ncurses_render(vm);
	}
	ncurses_render(vm);
	display_winner(vm);
	if (vm->param.is_ncurses)
		quit_ncurses(&(vm->ncurses));
	if (!flag & vm->param.is_dump)
	{
		ft_printf("Ending before end of dump\n");
		dump_memory(vm);
	}
	return (TRUE);
}
