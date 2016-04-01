#include "update_vm_info.h"

void	update_vm_info(t_vm *vm)
{
	WINDOW	*win;
	int		max_x;
	int		max_y;

	win = vm->ncurses.window[WIN_GLOB_INF];
	getmaxyx(win, max_y, max_x); 
	mvwprintw(win, 0, 0, "% *c", max_x - 1, ' ');
	mvwprintw(win, 0, 0, "Cycle to die: %d", vm->cycle_die.step);
	mvwprintw(win, 1, 0, "% *c", max_x - 1, ' ');
	mvwprintw(win, 1, 0, "Cycle delta: %d", CYCLE_DELTA);
	mvwprintw(win, 2, 0, "% *c", max_x - 1, ' ');
	mvwprintw(win, 2, 0, "Nb live: %d", vm->cycle_die.tot_live);
}
