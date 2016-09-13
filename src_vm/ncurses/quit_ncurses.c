#include "quit_ncurses.h"

static void	free_ncurses(t_ncurses *ncurses)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (ncurses->panel[i])
			del_panel(ncurses->panel[i]);
		++i;
	}
	i = 0;
	while (i < 3)
	{
		if (ncurses->window[i])
			delwin(ncurses->window[i]);
		if (ncurses->border[i])
			delwin(ncurses->border[i]);
		++i;
	}
	//delwin(ncurses->winner[0]);
}

void		quit_ncurses(t_ncurses *ncurses)
{
	while (1)
	{
		if (getch() != ERR)
		{
			free_ncurses(ncurses);
			endwin();
			return ;
		}
		usleep(5000);
	}
}
