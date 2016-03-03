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

	i = 0;
	while (i < vm->nb_players)
	{
		execute_player_process(vm->players + i, vm);
		++i;
	}
	return (TRUE);
}
