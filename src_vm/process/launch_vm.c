#include "launch_vm.h"

static int	init_player_process(t_player *player, size_t pos)
{
	t_process	*process;

	process = safe_malloc(sizeof(t_process));
	ft_bzero(process, sizeof(t_process));
	process->reg[0] = player->nb;
	process->pc = pos;
	process->number_cycles = 0;
	process->player_nb = player->nb;
	ft_lstadd(&(player->lst_process), ft_lstnew(process, sizeof(t_process)));
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
		ft_memcpy(vm->mem_space + off, player->bin, player->size_bin);
		init_player_process(player, off);
		++i;
	}
	return (TRUE);
}

static int	init_vm_function(t_vm *vm)
{
	vm->ins_function[0] = ins_live;
	vm->ins_function[1] = ins_ld;
	vm->ins_function[2] = ins_st;
	vm->ins_function[4] = ins_sub;
	vm->ins_function[6] = ins_or;
	vm->ins_function[8] = ins_zjump;
	return (TRUE);
}

static int	init_vm(t_vm *vm)
{
	vm->mem_space = safe_malloc(MEM_SIZE);
	ft_bzero(vm->mem_space, MEM_SIZE);
	write_player(vm);
	init_vm_function(vm);
	return (TRUE);
}

int			launch_vm(t_vm *vm)
{
	int		i;

	i = 0;
	init_vm(vm);
	while (1)
	{
		execute_loop(vm);
		if (vm->param.is_dump && vm->param.nb_cycle_dump == i)
		{
			dump_memory(vm);
			break ;
		}
		++i;
	}
	return (TRUE);
}
