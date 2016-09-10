#include "ins_fn.h"

static void		add_line(t_ncurses *ncurses, t_process *proc)
{
	char	*inf_str;
	char	*res;
	char	*val1;
	char	*reg;

	inf_str = get_proc_player_str(proc);
	val1 = ft_itoa(proc->curr_ins.param_val[0]);
	reg = get_reg_str(proc, P_VAL_2);
	res = ft_strnew(ft_strlen(val1) + ft_strlen("ld ") + ft_strlen(inf_str) + ft_strlen(reg) + 1);
	ft_strcpy(res, inf_str);
	ft_strcat(res, "ld ");
	ft_strcat(res, val1);
	ft_strcat(res, " ");
	ft_strcat(res, reg);
	printf("proc: %d\n", proc->curr_ins.opcode);
	add_ins_line(ncurses, get_param_str(proc));
	free(reg);
	free(val1);
	free(inf_str);
}

void	ins_ld(t_vm *vm, t_process *proc)
{
	int		val;

	printf("opcode: %d\n", proc->curr_ins.opcode);
	if (P_TYPE_1 & T_IND)
		val = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_1 % IDX_MOD));
	else
		val = P_VAL_1;
	proc->reg[P_VAL_2 - 1] = val;
	proc->carry = !val;
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_line(&vm->ncurses, proc);
}
