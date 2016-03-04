#include "execute_loop.h"

static int	execute_player_process(t_player *player, t_vm *vm)
{
	t_list	*process;

	process = player->lst_process;
	while (process)
	{
		execute_process(process->content, vm);
		process = process->next;
	}
	return (TRUE);
}

int			execute_loop(t_vm *vm)
{
	int		i;

	i = vm->nb_players;
	while (i--)
	{
		if (vm->players[i].is_alive)
			execute_player_process(vm->players + i, vm);
	}
	return (check_live(vm));
}
