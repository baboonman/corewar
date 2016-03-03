#include "ins_fn.h"

void			ins_add(t_vm *vm, t_process *proc)
{
	(void)vm;
	proc->reg[P_VAL_3 - 1] = proc->reg[P_VAL_1 - 1] + proc->reg[P_VAL_2 - 1];
	proc->carry = 1;
}
