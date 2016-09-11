#include "ins_fn.h"

void			ins_lldi(t_vm *vm, t_process *proc)
{
	int			p1;
	int			p2;

	if (P_TYPE_1 & T_REG)
		p1 = proc->reg[P_VAL_1 - 1];
	else if (P_TYPE_1 & T_IND)
		p1 = read_n_bytes(4, vm->mem_space, proc->pc + P_VAL_1);
	else
		p1 = P_VAL_1;
	if (P_TYPE_2 & T_REG)
		p2 = proc->reg[P_VAL_2 - 1];
	else
		p2 = P_VAL_2;
	proc->reg[P_VAL_3 - 1] = read_n_bytes(REG_SIZE, vm->mem_space,
								proc->pc + (p1 + p2));
	proc->carry = !(proc->reg[P_VAL_3 - 1]);
	proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
	add_ins_line(&vm->ncurses, get_str_ins(proc));
}
