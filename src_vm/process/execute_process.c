#include "execute_process.h"

void			decode_opc(uint8_t opc, t_ins *ins, int nb_param)
{
	int			i;

	i = 0;
	while (i < nb_param)	
	{
		if (((opc >> (8 - (i + 1) * 2)) & 0b00000011) == REG_CODE)
			ins->param_type[i] = T_REG;
		else if (((opc >> (8 - (i + 1) * 2)) & 0b00000011) == IND_CODE)
			ins->param_type[i] = T_IND;
		else if (((opc >> (8 - (i + 1) * 2)) & 0b00000011) == DIR_CODE)
			ins->param_type[i] = T_DIR;
		i++;
	}
	ins->size++;
}

void			decode_param(t_process *proc, int nb_param, void *mem_space,
								int idx)
{
	int			i;
	int			size;
	int			param;

	i = -1;
	while (++i < nb_param)
	{
		if (proc->curr_ins.param_type[i] & T_REG)
			size = 1;
		else if (proc->curr_ins.param_type[i] & T_IND || idx)
			size = IND_SIZE;
		else if (proc->curr_ins.param_type[i] & T_DIR)
			size = DIR_SIZE;
		param = read_n_bytes(size, mem_space, proc->pc + proc->curr_ins.size);
		proc->curr_ins.param_val[i] = param;
		proc->curr_ins.size += size;
	}
}

int				load_ins(t_process *proc, void *mem_space)
{
	t_op		*op_info;
	uint8_t		opc;

	proc->curr_ins.opcode = *((uint8_t*)(mem_space + proc->pc)) - 1;
	if (proc->curr_ins.opcode < 0 || proc->curr_ins.opcode > 15)
		return (0);
	proc->curr_ins.size = 1;
	op_info = &(g_op_tab[proc->curr_ins.opcode]);
	if (op_info->has_opc)
	{
		opc = read_n_bytes(1, mem_space, proc->pc + 1);
		decode_opc(opc, &(proc->curr_ins), op_info->nb_param);
	}
	else
		proc->curr_ins.param_type[0] = op_info->param_type[0];
	decode_param(proc, op_info->nb_param, mem_space,
					op_info->has_idx);
	return (op_info->nb_cycle);
}

void			print_ins(t_ins *ins)
{
	printf("opcode: %d\nparam_type: %d - %d - %d\nparam_val: %d - %d - %d\nsize: %lu\n",
			ins->opcode, 
			ins->param_type[0],
			ins->param_type[1],
			ins->param_type[2],
			ins->param_val[0],
			ins->param_val[1],
			ins->param_val[2],
			ins->size);
}

static int		execute_ins(t_vm *vm, t_process *proc)
{
	void		(*fn)(t_vm *, t_process *);

	fn = vm->ins_function[proc->curr_ins.opcode];
	fn(vm, proc);
	return (TRUE);
}

int				execute_process(t_process *proc, t_vm *vm)
{
	int			nb_cycles;

	nb_cycles = proc->number_cycles;
	if (nb_cycles > 1)
		proc->number_cycles--;
	else if (nb_cycles == 1)
	{
		execute_ins(vm, proc);
		proc->number_cycles--;
		proc->pc = (proc->pc + proc->curr_ins.size) % MEM_SIZE;
		proc->number_cycles = load_ins(proc, vm->mem_space);
		if (!proc->number_cycles)
			proc->pc++;
	}
	if (nb_cycles == 0)
	{
		proc->number_cycles = load_ins(proc, vm->mem_space);
		if (!proc->number_cycles)
			proc->pc++;
		else
			proc->number_cycles--;
	}
	return TRUE;
}
