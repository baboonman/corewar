#include "execute_process.h"

void			decode_opc(uint8_t opc, t_ins *ins, int nb_param)
{
	int			i;

	i = 0;
	fflush(0);
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
		{
			size = 1;
			param = *((uint8_t*)(mem_space + proc->pc + proc->curr_ins.size));
		}
		else if (proc->curr_ins.param_type[i] & T_IND || idx)
		{
			size = IND_SIZE;
			param = *((uint16_t*)(mem_space + proc->pc + proc->curr_ins.size));
		}
		else if (proc->curr_ins.param_type[i] & T_DIR)
		{
			size = DIR_SIZE;
			param = *((uint32_t*)(mem_space + proc->pc + proc->curr_ins.size));
		}
		proc->curr_ins.param_val[i] = swap_nbytes(param, size);
		proc->curr_ins.size += size;
	}
}

int				load_ins(t_process *proc, void *mem_space)
{
	t_op		*op_info;
	uint8_t		opc;

	proc->curr_ins.opcode = *((uint8_t*)(mem_space + proc->pc));
	proc->curr_ins.size = 1;
	op_info = &(g_op_tab[proc->curr_ins.opcode - 1]);
	if (op_info->has_opc)
	{
		opc = *((uint8_t*)mem_space + proc->pc + 1);
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
