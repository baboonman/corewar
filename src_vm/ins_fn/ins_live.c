#include "ins_fn.h"

void	ins_live(t_vm *vm, t_process *proc)
{
	int			i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->players[i].nb != proc->curr_ins.param_val[0])
		{
			++i;
			continue ;
		}
		vm->players[i].nb_live++;
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		return ;
	}
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
}
