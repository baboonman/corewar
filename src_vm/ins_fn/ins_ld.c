#include "ins_fn.h"

void	ins_ld(t_vm *vm, t_process *proc)
{
	int		val;

	if (proc->curr_ins.param_type[0] & T_IND)
		val = read_n_bytes(4, vm->mem_space,
				proc->pc + (proc->curr_ins.param_val[0] % IDX_MOD));
	else
		val = proc->curr_ins.param_val[0];
	proc->reg[proc->curr_ins.param_val[1] - 1] = val;
}
