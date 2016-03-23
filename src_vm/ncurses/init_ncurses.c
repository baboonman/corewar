#include "init_ncurses.h"

static void	set_init_val(void)
{
	initscr();
	noecho();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
}

int		init_ncurses(t_ncurses *ncurses)
{
	set_init_val();
	return (TRUE);
}
