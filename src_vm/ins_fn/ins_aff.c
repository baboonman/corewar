#include "ins_fn.h"

void			ins_aff(t_vm *vm, t_process *proc)
{
//	int			msg;

	(void)vm;
//	msg = proc->reg[P_VAL_1 - 1] % 256;
//	write(1, &msg, 1);
	ft_printf("%d\n", proc->reg[P_VAL_1 - 1]);
}
