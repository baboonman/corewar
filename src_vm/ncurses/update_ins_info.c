#include "update_ins_info.h"

void	update_ins_info(t_vm *vm)
{
	int		i;
	WINDOW	*win;
	int		max_x;
	int		max_y;
	int		pos;
	int		player_color;

	win = vm->ncurses.window[WIN_INS];
	getmaxyx(win, max_y, max_x); 
	i = 0;
	pos = vm->ncurses.pos - 1;
	while (i < vm->ncurses.size)
	{
		player_color = find_player_by_nb_player(vm, vm->ncurses.lst_ins[(pos) % NB_INS_DISPLAY]->player_id);
		wattron(vm->ncurses.window[WIN_INS], COLOR_PAIR(player_color));
		mvwprintw(win, i, 0, "% *c", max_x - 1, ' ');
		mvwprintw(win, i, 0, "%s",
				vm->ncurses.lst_ins[(pos) % NB_INS_DISPLAY]->str);
		wattroff(vm->ncurses.window[WIN_INS], COLOR_PAIR(player_color));
		pos--;
		if (pos < 0)
			pos = vm->ncurses.size - 1;
		++i;
	}
}
