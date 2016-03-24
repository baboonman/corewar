#include "init_ncurses.h"

static void	set_init_val(void)
{
	initscr();
	noecho();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
}

static int	create_borders(t_ncurses *ncurses)
{
	int		i;

	ncurses->border[WIN_INS] = newwin(INS_HEIGHT, INS_WIDTH,
			PLAYERS_INFO_HEIGHT, MEM_WIDTH + 1);
	if (!(ncurses->border[WIN_INS]))
		return (FALSE);

	ncurses->border[WIN_MEM] = newwin(MEM_HEIGHT, MEM_WIDTH,
			PLAYERS_INFO_HEIGHT, 0);
	if (!(ncurses->border[WIN_MEM]))
		return (FALSE);

	ncurses->border[WIN_INFO] = newwin(PLAYERS_INFO_HEIGHT, PLAYERS_INFO_WIDTH,
			0, 0);
	if (!(ncurses->border[WIN_INFO]))
		return (FALSE);
	i = 0;
	while (i < 3)
		box(ncurses->border[i++], ACS_VLINE, ACS_HLINE);
	return (TRUE);
}

static int	set_panel(t_ncurses *ncurses)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(ncurses->panel[i] = new_panel(ncurses->border[i])))
			return (FALSE);
		++i;
	}
	update_panels();
	doupdate();
	return (TRUE);
}

int			init_ncurses(t_ncurses *ncurses)
{
	set_init_val();
	create_borders(ncurses);
	set_panel(ncurses);
	
	return (TRUE);
}
