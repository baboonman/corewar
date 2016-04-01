#include "ins_fn.h"

static void	add_line(t_ncurses *ncurses, int val, t_process *proc)
{
	char	*str;
	char	*nb;
	char	*inf_str;

	if (!(nb = ft_itoa(val)))
		return ;
	if (!(inf_str = get_proc_player_str(proc)))
	{
		free(nb);
		return ;
	}
	str = ft_strnew(ft_strlen("live ") + ft_strlen(nb) + ft_strlen(inf_str) + 2);
	if (!str)
	{
		free(inf_str);
		free(nb);
		return ;
	}
	ft_strcpy(str, inf_str);
	ft_strcat(str, "live ");
	ft_strcat(str, nb);
	free(nb);
	free(inf_str);
	add_ins_line(ncurses, str);
}

void		ins_live(t_vm *vm, t_process *proc)
{
	int			i;

	i = 0;
	proc->nb_live++;
	add_line(&(vm->ncurses), proc->curr_ins.param_val[0], proc);
	while (i < vm->nb_players)
	{
		if (vm->players[i].nb != proc->curr_ins.param_val[0])
		{
			++i;
			continue ;
		}
		vm->players[i].nb_live++;
		if (vm->param.verbose)
			ft_printf("Un processus dit que le joueur %d(%s) est en vie\n",
				vm->players[i].nb, vm->players[i].header.prog_name);
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		return ;
	}
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
}
