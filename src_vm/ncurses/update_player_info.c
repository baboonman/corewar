#include "update_player_info.h"

static void		display_player(t_player *player, int offset, t_vm *vm)
{
	char	*str;
	int		x;
	int		y;

	mvwprintw(vm->ncurses.window[WIN_INFO], 0,
			offset * PLAYERS_INFO_WIDTH / vm->nb_players, player->header.prog_name);
	if (!(str = ft_itoa(player->nb)))
		return ;
	wprintw(vm->ncurses.window[WIN_INFO], "(");
	wprintw(vm->ncurses.window[WIN_INFO], str);
	wprintw(vm->ncurses.window[WIN_INFO], ")");
	free(str);
	if (player->is_alive)
		wprintw(vm->ncurses.window[WIN_INFO], " is alive");
	else
		wprintw(vm->ncurses.window[WIN_INFO], " dead    ");
	mvwprintw(vm->ncurses.window[WIN_INFO], 1,
			offset * PLAYERS_INFO_WIDTH / vm->nb_players, "Nb live: ");
	if (!(str = ft_itoa(player->nb_live)))
		return ;
	getyx(vm->ncurses.window[WIN_INFO], y, x);
	wprintw(vm->ncurses.window[WIN_INFO], "            ");
	mvwprintw(vm->ncurses.window[WIN_INFO], y, x, str);
	free(str);
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
