#include "ins_fn.h"

void			ins_fork(t_vm *vm, t_process *proc)
{
	int			i;
	t_process	*n_proc;
	t_list		*list;

	i = 0;
	n_proc = safe_malloc(sizeof(t_process));
	ft_memcpy(n_proc, proc, sizeof(t_process));
	n_proc->pc = proc->pc + (P_VAL_1 % IDX_MOD);
	n_proc->number_cycles = 0;
	while (i < vm->nb_players)
	{
		if (vm->players[i].nb == proc->player_nb)
		{
			list = ft_lstnew(n_proc, sizeof(t_process));
			list->next = vm->players[i].lst_process;
			vm->players[i].lst_process = list;
			break ;
		}
		i++;
	}
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
}
