#include "display_utils.h"

int				find_player(t_vm *vm, t_process *proc)
{
	int			i;
	t_player	player;

	i = 0;
	while (i < vm->nb_players)
	{
		player = vm->players[i];
		if (player.nb == proc->player_nb)
			return (player.color);
		i++;
	}
	return (player.color);
}

void			display_mem(t_vm *vm, int size, int off, int player_col)
{
	int			i;
	int			y;
	int			x;
	uint8_t		val;

	i = 0;
	while (i < size)
	{
		off %= MEM_SIZE;
		val = *((uint8_t *)(vm->mem_space + off));
		y = off / MEM_LINE_SIZE;
		x = (off % MEM_LINE_SIZE) * 3 + 1;
		wattron(vm->ncurses.window[WIN_MEM], COLOR_PAIR(player_col));
		mvwprintw(vm->ncurses.window[WIN_MEM], y, x, "%02x", val);
		wattroff(vm->ncurses.window[WIN_MEM], COLOR_PAIR(player_col));
		off++;
		i++;
	}
}

void			print_cursor(t_vm *vm, int off, int player_col, int on)
{
	int			y;
	int			x;
	uint8_t		val;

	off %= MEM_SIZE;
	val = *((uint8_t *)(vm->mem_space + off));
	y = off / MEM_LINE_SIZE;
	x = (off % MEM_LINE_SIZE) * 3 + 1;
	wattron(vm->ncurses.window[WIN_MEM], COLOR_PAIR(player_col + 4 * on));
	mvwprintw(vm->ncurses.window[WIN_MEM], y, x, "%02x", val);
	wattroff(vm->ncurses.window[WIN_MEM], COLOR_PAIR(player_col + 4 * on));
}

