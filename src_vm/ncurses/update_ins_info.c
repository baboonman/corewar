#include "update_ins_info.h"

void	update_ins_info(t_vm *vm)
{
	int		i;
	WINDOW	*win;
	int		max_x;
	int		max_y;
	int		pos;

	win = vm->ncurses.window[WIN_INS];
	getmaxyx(win, max_y, max_x); 
	i = 0;
	pos = vm->ncurses.pos - 1;
	while (i < vm->ncurses.size)
	{
		mvwprintw(win, i, 0, "% *c", max_x - 1, ' ');
		mvwprintw(win, i, 0, "%s",
				vm->ncurses.lst_ins[(pos) % NB_INS_DISPLAY]);
		pos--;
		if (pos < 0)
			pos = vm->ncurses.size - 1;
		++i;
	}
}
