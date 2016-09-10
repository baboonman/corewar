#include "init_mem.h"

static void		write_players(t_vm *vm)
{
	int			i;
	int			offset;
	t_player	*player;
	size_t		off;

	i = 0;
	offset = MEM_SIZE / vm->nb_players;
	while (i < vm->nb_players)
	{
		player = vm->players + i;
		off = i * offset;
		display_mem(vm, player->size_bin - sizeof(t_header), off, player->color);
		++i;
	}
}

void			init_mem(t_vm *vm, t_ncurses *ncurses)
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
	write_players(vm);
}
