/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_zjump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ins_fn.h"

static void	custom_msg(t_vm *vm, t_process *proc)
{
	t_disp_ins	*disp_ins;
	char		*res;
	char		*str;

	if (proc->carry)
		str = " OK";
	else
		str = " FAIL";
	disp_ins = get_str_ins(proc);
	res = ft_strnew(ft_strlen(disp_ins->str) + ft_strlen(str));
	ft_strcat(res, disp_ins->str);
	ft_strcat(res, str);
	free(disp_ins->str);
	disp_ins->str = res;
	add_ins_line(&vm->ncurses, disp_ins);
}

void		ins_zjump(t_vm *vm, t_process *proc)
{
	(void)vm;
	custom_msg(vm, proc);
	if (!proc->carry)
	{
		if (vm->param.verbose)
			ft_printf("zjmp fail (size: %d)\n", proc->curr_ins.size);
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		return ;
	}
	proc->pc = (proc->pc + (P_VAL_1 % IDX_MOD)) % MEM_SIZE;
}
