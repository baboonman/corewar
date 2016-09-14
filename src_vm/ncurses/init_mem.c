#include "init_mem.h"

void			init_mem(t_ncurses *ncurses)
{
	int			i;
	int			j;

	i = 0;
	while (i < MEM_HEIGHT)
	{
		j = 0;
		while (j < MEM_WIDTH - 2)
		{
			if ((j % 3) == 0)
				mvwprintw(ncurses->window[WIN_MEM], i, j, " ");
			else
				mvwprintw(ncurses->window[WIN_MEM], i, j, "0");
			j++;
		}
		i++;
	}
}
