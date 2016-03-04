#include "check_live.h"

static int	check_player_alive(t_vm *vm)
{
	int		i;
	int		tot_live;

	i = 0;
	tot_live = 0;
	while (i < vm->nb_players)
	{
		if (!vm->players[i].is_alive)
		{
			++i;
			continue ;
		}
		if (!vm->players[i].nb_live)
		{
			vm->players[i].is_alive = FALSE;
			++i;
			continue ;
		}
		tot_live += vm->players[i].nb_live;
		vm->players[i].nb_live = 0;
		++i;
	}
}

int			check_live(t_vm *vm)
{
	int		nb_live;

	if (vm->cycle_die.to_die == 0)
	{
		nb_live = check_players_alive(vm);
		if (nb_live >= NBR_LIVE || )
		{
			vm->cycle_die.step -= CYCLE_DELTA;
			vm->cycle_die.nb_cycle = 0;
		}
		else
			vm->cycle_die.nb_cycle++;

	}
}
