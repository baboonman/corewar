#include "ins_fn.h"

void	ins_sub(t_vm *vm, t_process *proc)
{
	(void)vm;
	proc->reg[P_VAL_3 - 1] = proc->reg[P_VAL_1 - 1] - proc->reg[P_VAL_2 - 1];
	proc->carry = !(proc->reg[P_VAL_3 - 1]);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
