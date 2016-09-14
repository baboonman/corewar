/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_lld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ins_fn.h"

void	ins_lld(t_vm *vm, t_process *proc)
{
	int		val;

	if (P_TYPE_1 & T_IND)
		val = read_n_bytes(4, vm->mem_space,
				proc->pc + P_VAL_1);
	else
		val = P_VAL_1;
	proc->reg[P_VAL_2 - 1] = val;
	proc->carry = !(proc->reg[P_VAL_2 - 1]);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
