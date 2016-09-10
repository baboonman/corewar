#include "ins_fn.h"

static void		add_line(t_ncurses *ncurses, t_process *proc)
{
	char	*inf_str;
	char	*dir;
	char	*res;

	inf_str = get_proc_player_str(proc);
	dir = ft_itoa(proc->curr_ins.param_val[0]);
	res = ft_strnew(ft_strlen(dir) + ft_strlen("ldi ") + ft_strlen(inf_str));
	ft_strcpy(res, inf_str);
	ft_strcat(res, "ldi ");
	ft_strcat(res, dir);
	add_ins_line(ncurses, get_param_str(proc));
	free(dir);
	free(inf_str);
}

void			ins_ldi(t_vm *vm, t_process *proc)
{
	int			p1;
	int			p2;

	if (P_TYPE_1 & T_REG)
		p1 = proc->reg[P_VAL_1 - 1];
	else if (P_TYPE_1 & T_IND)
		p1 = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_1 % IDX_MOD));
	else
		p1 = P_VAL_1;
	if (P_TYPE_2 & T_REG)
		p2 = proc->reg[P_VAL_2 - 1];
	else
		p2 = P_VAL_2;
	proc->reg[P_VAL_3 - 1] = read_n_bytes(REG_SIZE, vm->mem_space,
								proc->pc + ((p1 + p2) % IDX_MOD));
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_line(&vm->ncurses, proc);
}
