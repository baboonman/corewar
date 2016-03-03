#include "ins_fn.h"

void			ins_lfork(t_vm *vm, t_process *proc)
{
	int			i;
	t_process	*n_proc;

	(void)vm;
	i = 0;
	n_proc = safe_malloc(sizeof(t_process));
	ft_memcpy(n_proc, proc, sizeof(t_process));
	n_proc->pc = proc->pc + P_VAL_1;
	while (i < vm->nb_players)
	{
		if (vm->players[i].nb == proc->player_nb)
		{
			ft_lstadd(&(vm->players[i].lst_process), ft_lstnew(n_proc,
						sizeof(t_process)));
			break ;
		}
		i++;
	}
}
