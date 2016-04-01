#include "ins_fn.h"

static void		add_line(t_ncurses *ncurses, t_process *proc, int p1, int p2)
{
	char	*inf_str;
	char	*p[3];
	char	*res;
	size_t	res_size;

	res_size = 4;
	inf_str = get_proc_player_str(proc);
	res_size += ft_strlen("and ");
	res_size += ft_strlen(inf_str);
	if (P_TYPE_1 & T_REG)
		p[0] = get_reg_str(proc, P_VAL_1);
	else
		p[0] = get_itoa_space(p1);
	if (P_TYPE_2 & T_REG)
		p[1] = get_reg_str(proc, P_VAL_2);
	else
		p[1] = get_itoa_space(p2);
	p[2] = get_reg_str(proc, P_VAL_3);
	res_size += ft_strlen(p[0]);
	res_size += ft_strlen(p[1]);
	res_size += ft_strlen(p[2]);
	res = ft_strnew(res_size);
	ft_strcpy(res, inf_str);
	ft_strcat(res, "and ");
	ft_strcat(res, p[0]);
	ft_strcat(res, p[1]);
	ft_strcat(res, p[2]);
	add_ins_line(ncurses, res);
	free(p[0]);
	free(p[1]);
	free(p[2]);
	free(inf_str);
}

void			ins_and(t_vm *vm, t_process *proc)
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
	else if (P_TYPE_2 & T_IND)
		p2 = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_2 % IDX_MOD));
	else
		p2 = P_VAL_2;
	proc->reg[P_VAL_3 - 1] = p1 & p2;
	proc->carry = !(proc->reg[P_VAL_3 - 1]);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_line(&vm->ncurses, proc, p1, p2);
}
