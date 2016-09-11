#include "ins_fn.h"

void			ins_aff(t_vm *vm, t_process *proc)
{
	int			msg;

	(void)vm;
	msg = proc->reg[P_VAL_1 - 1] % 256;
	if (!vm->param.is_ncurses)
		write(1, &msg, 1);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
