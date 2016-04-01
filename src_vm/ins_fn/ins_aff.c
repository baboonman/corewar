#include "ins_fn.h"

static void		add_line(t_ncurses *ncurses, t_process *proc, int msg)
{
	char	*inf_str;
	char	*res;

	inf_str = get_proc_player_str(proc);
	res = ft_strnew(ft_strlen(inf_str) + 5);
	ft_strcpy(res, inf_str);
	ft_strcat(res, "aff ");
	res[ft_strlen(res)] = (char)msg;
	add_ins_line(ncurses, res);
	free(inf_str);
}

void			ins_aff(t_vm *vm, t_process *proc)
{
	int			msg;

	(void)vm;
	msg = proc->reg[P_VAL_1 - 1] % 256;
	if (!vm->param.is_ncurses)
		write(1, &msg, 1);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_line(&vm->ncurses, proc, msg);
}
