#include "display_winner.h"

static void	display_player(t_vm *vm, int id_max, int pos)
{
	mvwprintw(vm->ncurses.winner[0], (pos - 1) * 2, 1 , "TOTOTOTOTOTOTOTOTOTO");

}

static void	display_all_player(t_vm *vm)
{
	int			i;
	int			*already_check;
	int			max;
	int			id_max;
	int			j;

	i = 0;
	already_check = safe_malloc(sizeof(int) * vm->nb_players);
	ft_bzero(already_check, sizeof(int) * vm->nb_players);
	while (i < vm->nb_players)
	{
		max = 0;
		j = 0;
		while (j < vm->nb_players)
		{
			if ((!already_check[j]) && vm->players.die_at > max)
			{
				max = vm->players.die_at;
				id_max = j;
			}
			j++;
		}
		already_check[id_max] = 1;
		display_player(vm, id_max, i);
		i++;
	}
	free(already_check);
}

void		display_winner(t_vm *vm)
{
	vm->ncurses.winner[0] = newwin(30, 100, 10, 45);
	if (!vm->ncurses.winner[0])
		return ;
	box(vm->ncurses.winner[0], ACS_VLINE, ACS_HLINE);
	mvwprintw(vm->ncurses.winner[0], 5, 0, "TOTOTOTOTOTOTOTOTOTO");
	PANEL	*pan = new_panel(vm->ncurses.winner[0]);
	update_panels();
	doupdate();
}
