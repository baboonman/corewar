#ifndef DISPLAY_UTILS_H
# define DISPLAY_UTILS_H

# include "init_ncurses.h"
# include "process_struct.h"

int				find_player(t_vm *vm, t_process *proc);
void			display_mem(t_vm *vm, int size, int off, int player_col);

#endif
