#include "check_live.h"

static int	check_process_alive(t_vm *vm)
{
	t_list		*lst_proc;
	t_list		*tmp;
	t_process	*proc;

	lst_proc = vm->lst_process;
	while (lst_proc)
	{
		tmp = lst_proc->next;
		proc = lst_proc->content;
		if (proc->nb_live == 0)
		{
			if (vm->param.verbose)
				ft_printf("A processus of the player %d die\n", proc->player_nb);
			free(proc);
			ft_lstdelone(&(vm->lst_process), lst_proc);
			vm->nb_proc--;
		}
		else
			proc->nb_live = 0;
		lst_proc = tmp;
	}
	return (TRUE);
}

static int	check_players_alive(t_vm *vm)
{
	int		i;
	int		tot_live;

	i = 0;
	tot_live = 0;
	while (i < vm->nb_players)
	{
		if (vm->param.verbose)
			ft_printf("Total live: %d\n", vm->players[i].nb_live);
		if (!(vm->players[i].is_alive))
		{
			++i;
			vm->players[i].nb_live = 0;
			continue ;
		}
		tot_live += vm->players[i].nb_live;
		if (!vm->players[i].nb_live)
		{
			vm->players[i].is_alive = FALSE;
			vm->players[i].die_at = vm->tot_cycle;
			if (!vm->param.is_ncurses)
				ft_printf("player: %d, %s die\n", vm->players[i].nb, vm->players[i].header.prog_name);
			vm->players[i].nb_live = 0;
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

static int	get_all_live(t_vm *vm)
{
	int		i;
	int		tot;

	tot = 0;
	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->players[i].is_alive)
			tot += vm->players[i].nb_live;
		++i;
	}
	return (tot);
}

int			check_live(t_vm *vm)
{
	int		nb_live;

	nb_live = 0;
	if (vm->cycle_die.to_die <= 0)
	{
		check_process_alive(vm);
		nb_live = check_players_alive(vm);
		if (nb_live >= NBR_LIVE || vm->cycle_die.nb_cycle >= MAX_CHECKS)
		{
			vm->cycle_die.step -= CYCLE_DELTA;
			vm->cycle_die.nb_cycle = 0;
			if (vm->param.verbose)
				ft_printf("CTD decrement (%d)\n", vm->cycle_die.step);
		}
		else
			vm->cycle_die.nb_cycle++;
		vm->cycle_die.to_die = vm->cycle_die.step;
	}
	vm->cycle_die.to_die--;
	vm->cycle_die.tot_live = get_all_live(vm);
	return (check_alive(vm));
}
