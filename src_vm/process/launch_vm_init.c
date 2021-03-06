/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_vm_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:35 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launch_vm.h"

static int		init_player_process(t_vm *vm, t_player *player, size_t pos)
{
	t_process	*process;
	t_list		*list;

	process = safe_malloc(sizeof(t_process));
	ft_bzero(process, sizeof(t_process));
	process->reg[0] = player->nb;
	process->pc = pos;
	process->number_cycles = 0;
	process->player_nb = player->nb;
	process->proc_nb = vm->nb_proc++;
	list = ft_lstnew(process, sizeof(t_process));
	list->next = vm->lst_process;
	vm->lst_process = list;
	return (TRUE);
}

static int		write_player(t_vm *vm)
{
	int			i;
	int			offset;
	t_player	*player;
	size_t		off;

	i = 0;
	offset = MEM_SIZE / vm->nb_players;
	while (i < vm->nb_players)
	{
		player = vm->players + i;
		off = i * offset;
		ft_memcpy(vm->mem_space + off, player->bin,
				player->size_bin - sizeof(t_header));
		ft_memset(vm->mem_space_col + off, player->color,
				(player->size_bin - sizeof(t_header)));
		init_player_process(vm, player, off);
		++i;
	}
	return (TRUE);
}

static int		init_vm_function(t_vm *vm)
{
	vm->ins_function[0] = ins_live;
	vm->ins_function[1] = ins_ld;
	vm->ins_function[2] = ins_st;
	vm->ins_function[3] = ins_add;
	vm->ins_function[4] = ins_sub;
	vm->ins_function[5] = ins_and;
	vm->ins_function[6] = ins_or;
	vm->ins_function[7] = ins_xor;
	vm->ins_function[8] = ins_zjump;
	vm->ins_function[9] = ins_ldi;
	vm->ins_function[10] = ins_sti;
	vm->ins_function[11] = ins_fork;
	vm->ins_function[12] = ins_lld;
	vm->ins_function[13] = ins_lldi;
	vm->ins_function[14] = ins_lfork;
	vm->ins_function[15] = ins_aff;
	return (TRUE);
}

int				init_vm(t_vm *vm)
{
	vm->nb_proc = 0;
	vm->mem_space = safe_malloc(MEM_SIZE * 4);
	ft_bzero(vm->mem_space, MEM_SIZE);
	vm->mem_space_col = (uint8_t*)safe_malloc(MEM_SIZE);
	ft_bzero(vm->mem_space_col, MEM_SIZE);
	write_player(vm);
	init_vm_function(vm);
	vm->cycle_die.to_die = CYCLE_TO_DIE;
	vm->cycle_die.step = CYCLE_TO_DIE;
	if (vm->param.is_ncurses)
		return (init_ncurses(&(vm->ncurses), vm));
	return (1);
}

int				init_launch_vm(t_vm *vm, t_loop_param *p, int *i, int *flag)
{
	gettimeofday(&(p->a), NULL);
	*i = 0;
	*flag = 0;
	if (!init_vm(vm))
		return (FALSE);
	init_input(&(p->input));
	return (TRUE);
}
