#include "ins_fn.h"

void	ins_zjump(t_vm *vm, t_process *proc)
{
	if (!proc->carry)
		return ;
	proc->pc += (P_VAL_1 % IDX_MOD);
}
