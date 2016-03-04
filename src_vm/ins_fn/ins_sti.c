#include "ins_fn.h"

void	ins_sti(t_vm *vm, t_process *proc)
{
	int		l_val;
	int		r_val;

	if (P_TYPE_2 & T_REG)
		l_val = proc->reg[P_VAL_2 - 1];
	else if (P_TYPE_2 & T_DIR)
		l_val = P_VAL_2;
	else
		l_val = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_2 % IDX_MOD));
	if (P_TYPE_3 & T_REG)
		r_val = proc->reg[P_VAL_3 - 1];
	else
		r_val = P_VAL_3;
	write_n_bytes(4, vm->mem_space, proc->pc + ((l_val + r_val) % IDX_MOD),
			proc->reg[P_VAL_1 - 1]);
}