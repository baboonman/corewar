#include "display_winner.h"

static void	display_player(t_vm *vm, int id, int pos)
{
	char	*str;
	int		player_color;

	if (pos == 0)
		str = "win";
	else
		str = "suck";
	player_color = find_player_by_nb_player(vm, vm->players[id].nb);
	wattron(vm->ncurses.winner[0], COLOR_PAIR(player_color));
	mvwprintw(vm->ncurses.winner[0],
			pos + 1, 1, "%d) Player %s %s, he die at cycle %d", pos + 1,
			vm->players[id].header.prog_name, str, vm->players[id].die_at);
	wattroff(vm->ncurses.winner[0], COLOR_PAIR(player_color));
}

static void	display_all_players(t_vm *vm)
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
		j = -1;
		while (++j < vm->nb_players)
		{
			if ((!already_check[j]) && vm->players[j].die_at > max)
			{
				max = vm->players[j].die_at;
				id_max = j;
			}
		}
		already_check[id_max] = 1;
		display_player(vm, id_max, i++);
	}
	free(already_check);
}

void		display_winner(t_vm *vm)
{
	vm->ncurses.winner[0] = newwin(30, 100, 10, 45);
	if (!vm->ncurses.winner[0])
		return ;
	box(vm->ncurses.winner[0], ACS_VLINE, ACS_HLINE);
	new_panel(vm->ncurses.winner[0]);
	display_all_players(vm);
	update_panels();
	doupdate();
}
