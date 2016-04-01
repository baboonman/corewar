#include "ins_fn.h"

static void		add_line(t_ncurses *ncurses, t_process *proc)
{
	char	*inf_str;
	char	*r[3];
	char	*res;
	size_t	res_size;

	res_size = 4;
	inf_str = get_proc_player_str(proc);
	res_size += ft_strlen("add ");
	res_size += ft_strlen(inf_str);
	r[0] = get_reg_str(proc, P_VAL_1);
	r[1] = get_reg_str(proc, P_VAL_2);
	r[2] = get_reg_str(proc, P_VAL_3);
	res_size += ft_strlen(r[0]);
	res_size += ft_strlen(r[1]);
	res_size += ft_strlen(r[2]);
	res = ft_strnew(res_size);
	ft_strcpy(res, inf_str);
	ft_strcat(res, "add ");
	ft_strcat(res, r[0]);
	ft_strcat(res, r[1]);
	ft_strcat(res, r[2]);
	add_ins_line(ncurses, res);
	free(r[0]);
	free(r[1]);
	free(r[2]);
	free(inf_str);
}

void			ins_add(t_vm *vm, t_process *proc)
{
	(void)vm;
	proc->reg[P_VAL_3 - 1] = proc->reg[P_VAL_1 - 1] + proc->reg[P_VAL_2 - 1];
	proc->carry = !(proc->reg[P_VAL_3 - 1]);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_line(&vm->ncurses, proc);
}
