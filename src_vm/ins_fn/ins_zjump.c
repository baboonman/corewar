#include "ins_fn.h"

void	ins_zjump(t_vm *vm, t_process *proc)
{
	(void)vm;
	if (!proc->carry)
	{
		if (vm->param.verbose)
			ft_printf("zjmp fail (size: %d)\n", proc->curr_ins.size);
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		return ;
	}
	proc->pc = (proc->pc + (P_VAL_1 % IDX_MOD)) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
