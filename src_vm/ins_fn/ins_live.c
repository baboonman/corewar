#include "ins_fn.h"

void	ins_live(t_vm *vm, t_process *proc)
{
	int			i;

	i = 0;
	proc->nb_live++;
	while (i < vm->nb_players)
	{
		if (vm->players[i].nb != proc->curr_ins.param_val[0])
		{
			++i;
			continue ;
		}
		vm->players[i].nb_live++;
		if (vm->param.verbose)
			ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
				vm->players[i].nb, vm->players[i].header.prog_name);
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		return ;
	}
		ft_printf("addr: %d\n", proc->pc);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
}
