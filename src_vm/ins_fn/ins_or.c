/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ins_fn.h"

void	ins_or(t_vm *vm, t_process *proc)
{
	int		l_val;
	int		r_val;

	if (P_TYPE_1 & T_REG)
		l_val = proc->reg[P_VAL_1 - 1];
	else if (P_TYPE_1 & T_DIR)
		l_val = P_VAL_1;
	else
		l_val = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_1 % IDX_MOD));
	if (P_TYPE_2 & T_REG)
		r_val = proc->reg[P_VAL_2 - 1];
	else if (P_TYPE_2 & T_DIR)
		r_val = P_VAL_2;
	else
		r_val = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_2 % IDX_MOD));
	proc->reg[P_VAL_3 - 1] = l_val | r_val;
	proc->carry = !(proc->reg[P_VAL_3 - 1]);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
