/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ins_fn.h"

void	ins_st(t_vm *vm, t_process *proc)
{
	int		src;

	src = proc->reg[P_VAL_1 - 1];
	add_ins_line(&vm->ncurses, get_str_ins(proc));
	if (proc->curr_ins.param_type[1] & T_IND)
	{
		write_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_2 % IDX_MOD), src);
		if (vm->param.is_ncurses)
			display_mem(vm, 4, proc->pc + (P_VAL_2 % IDX_MOD),
					find_player(vm, proc));
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		return ;
	}
	proc->reg[P_VAL_2 - 1] = src;
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
}
