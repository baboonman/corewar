#include "check_live.h"

static int	check_players_alive(t_vm *vm)
{
	int		i;
	int		tot_live;

	i = 0;
	tot_live = 0;
	while (i < vm->nb_players)
	{
		ft_printf("live: %d\n", vm->players[i].nb_live);
		tot_live += vm->players[i].nb_live;
		if (!(vm->players[i].is_alive))
		{
			++i;
			continue ;
		}
		if (!vm->players[i].nb_live)
		{
			vm->players[i].is_alive = FALSE;
			ft_printf("player: %d, %s die\n", vm->players[i].nb, vm->players[i].header.prog_name);
			++i;
			continue ;
		}
		vm->players[i].nb_live = 0;
		++i;
	}
	return (tot_live);
}

static int	check_alive(t_vm *vm)
{
	int		i;

	i = vm->nb_players;
	while (i--)
	{
		if (vm->players[i].is_alive)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

int			check_live(t_vm *vm)
{
	int		nb_live;

	nb_live = 0;
	if (vm->cycle_die.to_die <= 0)
	{
		nb_live = check_players_alive(vm);
		ft_printf("nb live: %d\n", nb_live);
		if (nb_live >= NBR_LIVE || vm->cycle_die.nb_cycle >= MAX_CHECKS)
		{
			vm->cycle_die.step -= CYCLE_DELTA;
			vm->cycle_die.nb_cycle = 0;
			ft_printf("CTD decrement (%d)\n", vm->cycle_die.step);
		}
		else
			vm->cycle_die.nb_cycle++;
		vm->cycle_die.to_die = vm->cycle_die.step;
	}
	vm->cycle_die.to_die--;
	return (check_alive(vm));
}
