#include "ins_fn.h"

void	ins_ld(t_vm *vm, t_process *proc)
{
	int		val;

	if (P_TYPE_1 & T_IND)
		val = read_n_bytes(4, vm->mem_space, proc->pc + (P_VAL_1 % IDX_MOD));
	else
		val = P_VAL_1;
	proc->reg[P_VAL_2 - 1] = val;
	proc->carry = !val;
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
