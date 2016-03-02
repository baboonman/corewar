#include "execute_process.h"

int				load_ins(t_process *proc, void *mem_space)
{
	t_op		*op_info;

	proc->curr_ins.opcode = *((uint8_t*)mem_space + proc->pc);

	return (TRUE);
}

void			print_ins(t_ins *ins)
{
	printf("opcode: %d\nparam_type: %c - %c - %c\n",
			ins->opcode, 
			ins->param_type[0],
			ins->param_type[1],
			ins->param_type[2]);
}

int				execute_process(t_process *proc, void *mem_space)
{
	int			nb_cycles;

	nb_cycles = proc->number_cycles;
	if (nb_cycles > 0)
	{
		proc->number_cycles--;
	}
	else if (nb_cycles == 0)
	{
		write(1, "nothing yet\n", 12);
		proc->number_cycles--;
	}
	else if (nb_cycles == -1)
	{
		proc->number_cycles = load_ins(proc, mem_space);
		print_ins(&proc->curr_ins);
	}
	return TRUE;
}
