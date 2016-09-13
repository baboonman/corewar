#ifndef DISPLAY_UTILS_H
# define DISPLAY_UTILS_H

# include "init_ncurses.h"
# include "process_struct.h"

int				find_player_by_nb_player(t_vm *vm, int player_nb);
int				find_player(t_vm *vm, t_process *proc);
void			display_mem(t_vm *vm, int size, int off, int player_col);
void			print_cursor(t_vm *vm, int off, int player_col, int on);
void			refresh_mem_display(t_vm* vm);

#endif
