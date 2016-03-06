#include "launch_vm.h"

static int	init_player_process(t_vm *vm, t_player *player, size_t pos)
{
	t_process	*process;

	process = safe_malloc(sizeof(t_process));
	ft_bzero(process, sizeof(t_process));
	process->reg[0] = player->nb;
	process->pc = pos;
	process->number_cycles = 0;
	process->player_nb = player->nb;
	ft_lstadd(&(vm->lst_process), ft_lstnew(process, sizeof(t_process)));
	return (TRUE);
}

static int	write_player(t_vm *vm)
{
	int			i;
	int			offset;
	t_player	*player;
	size_t		off;

	i = 0;
	offset = MEM_SIZE / vm->nb_players;
	while (i < vm->nb_players)
	{
		player = vm->players + i;
		off = i * offset;
		ft_memcpy(vm->mem_space + off, player->bin, player->size_bin - sizeof(t_header));
		init_player_process(vm, player, off);
		++i;
	}
	return (TRUE);
}

static int	init_vm_function(t_vm *vm)
{
	vm->ins_function[0] = ins_live;
	vm->ins_function[1] = ins_ld;
	vm->ins_function[2] = ins_st;
	vm->ins_function[3] = ins_add;
	vm->ins_function[4] = ins_sub;
	vm->ins_function[5] = ins_and;
	vm->ins_function[6] = ins_or;
	vm->ins_function[7] = ins_xor;
	vm->ins_function[8] = ins_zjump;
	vm->ins_function[9] = ins_ldi;
	vm->ins_function[10] = ins_sti;
	vm->ins_function[11] = ins_fork;
	vm->ins_function[12] = ins_lld;
	vm->ins_function[13] = ins_lldi;
	vm->ins_function[14] = ins_lfork;
	vm->ins_function[15] = ins_aff;
	return (TRUE);
}

static int	init_vm(t_vm *vm)
{
	vm->mem_space = safe_malloc(MEM_SIZE);
	ft_bzero(vm->mem_space, MEM_SIZE);
	write_player(vm);
	init_vm_function(vm);
	vm->cycle_die.to_die = CYCLE_TO_DIE;
	vm->cycle_die.step = CYCLE_TO_DIE;
	return (TRUE);
}

int			launch_vm(t_vm *vm)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	init_vm(vm);
	while (1)
	{
		if (!execute_loop(vm))
		{
			ft_printf("Nb loop: %d\n", i);
			dump_memory(vm);
			return (TRUE);
		}
		++i;
		if (vm->param.is_dump && vm->param.nb_cycle_dump <= i)
		{
			flag = 1;
			dump_memory(vm);
			break ;
		}
	}
	if (!flag)
		dump_memory(vm);
	return (TRUE);
}
