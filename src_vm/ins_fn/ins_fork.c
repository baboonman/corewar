#include "ins_fn.h"

static void		add_line(t_ncurses *ncurses, t_process *proc)
{
	char	*inf_str;
	char	*dir;
	char	*res;

	inf_str = get_proc_player_str(proc);
	res = ft_strnew(ft_strlen(dir) + ft_strlen("fork ") + ft_strlen(inf_str));
	ft_strcpy(res, inf_str);
	ft_strcat(res, "fork ");
	ft_strcat(dir);
	add_ins_line(ncurses, res);
	free(dir);
	free(inf_str);
}

void			ins_fork(t_vm *vm, t_process *proc)
{
	t_process	*n_proc;
	t_list		*list;

	n_proc = safe_malloc(sizeof(t_process));
	ft_memcpy(n_proc, proc, sizeof(t_process));
	n_proc->pc = proc->pc + (P_VAL_1 % IDX_MOD);
	n_proc->number_cycles = 0;
	n_proc->proc_nb = vm->nb_proc++;
	list = ft_lstnew(n_proc, sizeof(t_process));
	list->next = vm->lst_process;
	vm->lst_process = list;
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
}
