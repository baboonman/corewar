#include "update_vm_info.h"

void	update_vm_info(t_vm *vm)
{
	WINDOW	*win;
	int		max_x;
	int		max_y;

	win = vm->ncurses.window[WIN_GLOB_INF];
	getmaxyx(win, max_y, max_x); 
	mvwprintw(win, 0, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 0, 0, "Cycle to die: %d", vm->cycle_die.to_die);
	mvwprintw(win, 1, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 1, 0, "Cycle delta: %d", CYCLE_DELTA);
	mvwprintw(win, 2, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 2, 0, "Nb live: %d", vm->cycle_die.tot_live);
	mvwprintw(win, 3, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 3, 0, "Step: %d", vm->cycle_die.step);
	mvwprintw(win, 4, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 4, 0, "NB Proc: %d", vm->nb_proc);
	mvwprintw(win, 5, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 5, 0, "Tot cycle: %d", vm->tot_cycle);
	mvwprintw(win, 6, 0, "% *c", max_x + 1, ' ');
	mvwprintw(win, 6, 0, "fps: %d", vm->fps);
}
