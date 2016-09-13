#include "update_player_info.h"

static void		display_player(t_player *player, int offset, t_vm *vm)
{
	int		y;
	int		player_color;

	player_color = find_player_by_nb_player(vm, player->nb);
	wattron(vm->ncurses.window[WIN_INFO], COLOR_PAIR(player_color));
	mvwprintw(vm->ncurses.window[WIN_INFO], 0,
			offset * PLAYERS_INFO_WIDTH / vm->nb_players, "%s (%d)",
			player->header.prog_name, player->nb);
	if (player->is_alive)
		wprintw(vm->ncurses.window[WIN_INFO], " is alive");
	else
		wprintw(vm->ncurses.window[WIN_INFO], " dead    ");

	y = offset * PLAYERS_INFO_WIDTH / vm->nb_players;
	mvwprintw(vm->ncurses.window[WIN_INFO], 1, y, "% *c", 15, ' ');
	mvwprintw(vm->ncurses.window[WIN_INFO], 1,
			y, "Nb live: %d", player->nb_live);
	wattroff(vm->ncurses.window[WIN_INFO], COLOR_PAIR(player_color));
}

void			update_player_info(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		display_player(vm->players + i, i, vm);
		++i;
	}
}
