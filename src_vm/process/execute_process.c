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

int				decode_param(t_process *proc, int nb_param, void *mem_space,
								t_op *op_info)
{
	int			i;
	int			size;
	int			param;

	i = -1;
	while (++i < nb_param)
	{
		if (!(proc->curr_ins.param_type[i] & op_info->param_type[i]))
			return (FALSE);
		if (proc->curr_ins.param_type[i] & T_REG)
			size = 1;
		else if (proc->curr_ins.param_type[i] & T_IND || op_info->has_idx)
			size = IND_SIZE;
		else if (proc->curr_ins.param_type[i] & T_DIR)
			size = DIR_SIZE;
		param = read_n_bytes(size, mem_space, proc->pc + proc->curr_ins.size);
		if (size == 1 && (param < 1 || param > REG_NUMBER))
			return (FALSE);
		if (proc->curr_ins.param_type[i] & T_IND)
			param %= IDX_MOD;
		proc->curr_ins.param_val[i] = param;
		proc->curr_ins.size += size;
	}
	return (TRUE);
}

int				load_ins(t_process *proc, void *mem_space)
{
	t_op		*op_info;
	uint8_t		opc;

	proc->curr_ins.opcode = read_n_bytes(1, mem_space, proc->pc) - 1;
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
	return (op_info->nb_cycle);
}

static int		execute_ins(t_vm *vm, t_process *proc)
{
	void		(*fn)(t_vm *, t_process *);
	t_op		*op_info;

	op_info = &(g_op_tab[proc->curr_ins.opcode]);
	if (!decode_param(proc, op_info->nb_param, vm->mem_space, op_info))
		return (FALSE);
	if (vm->param.verbose)
	{
		ft_printf("P	%d, %d, %s, %d (%d), %d (%d), %d (%d)\n",
				proc->player_nb, proc->proc_nb, g_op_tab[proc->curr_ins.opcode].name_op,
				proc->curr_ins.param_val[0], proc->curr_ins.param_type[0],
				proc->curr_ins.param_val[1], proc->curr_ins.param_type[1],
				proc->curr_ins.param_val[2], proc->curr_ins.param_type[2]);
	}
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
		print_cursor(vm, proc->pc, find_player(vm, proc), 0);
		execute_ins(vm, proc);
		proc->number_cycles = load_ins(proc, vm->mem_space);
		if (!proc->number_cycles)
		{
			if (vm->param.verbose)
				ft_printf("execute invalid instruction\n");
			if (vm->param.is_ncurses)
				add_ins_line(&vm->ncurses, get_str_invalid(proc));
			print_cursor(vm, proc->pc, find_player(vm, proc), 0);
			proc->pc = (proc->pc + 1) % MEM_SIZE;
		}
	}
	if (nb_cycles == 0)
	{
		proc->number_cycles = load_ins(proc, vm->mem_space);
		if (!proc->number_cycles)
		{
			if (vm->param.verbose)
				ft_printf("Execute invalid instruction\n");
			if (vm->param.is_ncurses)
				add_ins_line(&vm->ncurses, get_str_invalid(proc));
			print_cursor(vm, proc->pc, find_player(vm, proc), 0);
			proc->pc = (proc->pc + 1) % MEM_SIZE;
		}
		else
			proc->number_cycles--;
	}
	return (TRUE);
}
