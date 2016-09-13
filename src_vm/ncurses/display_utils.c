#include "display_utils.h"

int				find_player(t_vm *vm, t_process *proc)
{
	return find_player_by_nb_player(vm, proc->player_nb);
}

int				find_player_by_nb_player(t_vm *vm, int player_nb)
{
	int			i;
	t_player	player;

	i = 0;
	while (i < vm->nb_players)
	{
		player = vm->players[i];
		if (player.nb == player_nb)
			return (player.color);
		i++;
	}
	return (player.color);
}


void			display_mem(t_vm *vm, int size, int off, int player_col)
{
	int			i;

	i = 0;
	while (i < size)
	{
		off %= MEM_SIZE;
		vm->mem_space_col[off] = (uint8_t)player_col;
		off++;
		i++;
	}
}

void			print_cursor(t_vm *vm, int off, int player_col, int on)
{
	off %= MEM_SIZE;
	vm->mem_space_col[off] = (uint8_t)(player_col + 4 * on);
}

void			refresh_mem_display(t_vm* vm)
{
	int			i;
	int			x;
	int			y;
	uint8_t		col;
	uint8_t		val;

	i = 0;
	while (i < MEM_SIZE)
	{
		col = vm->mem_space_col[i];
		val = *((uint8_t *)(vm->mem_space + i));
		y = i / MEM_LINE_SIZE;
		x = (i % MEM_LINE_SIZE) * 3 + 1;
		wattron(vm->ncurses.window[WIN_MEM], COLOR_PAIR(col));
		mvwprintw(vm->ncurses.window[WIN_MEM], y, x, "%02x", val);
		wattroff(vm->ncurses.window[WIN_MEM], COLOR_PAIR(col));
		i++;
	}
}
