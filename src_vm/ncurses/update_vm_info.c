#include "update_vm_info.h"

void	update_vm_info(t_vm *vm)
{
	char	*str;
	WINDOW	*win;
	int		x;
	int		y;

	win = vm->ncurses.window[WIN_GLOB_INF];
	mvwprintw(win, 0, 0, "Cycle to die: ");
	if (!(str = ft_itoa(vm->cycle_die.step)))
		return ;
	getyx(win, y, x);
	wprintw(win, SPACE_INT);
	mvwprintw(win, y, x, str);
	free(str);
	mvwprintw(win, 1, 0, "Cycle delta: ");
	if (!(str = ft_itoa(CYCLE_DELTA)))
		return ;
	getyx(win, y, x);
	wprintw(win, SPACE_INT);
	mvwprintw(win, y, x, str);
	free(str);
	mvwprintw(win, 2, 0, "Nb live: ");
	if (!(str = ft_itoa(vm->cycle_die.tot_live)))
		return ;
	getyx(win, y, x);
	wprintw(win, SPACE_INT);
	mvwprintw(win, y, x, str);
	free(str);
}
