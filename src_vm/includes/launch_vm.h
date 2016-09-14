#ifndef LAUNCH_VM_H
# define LAUNCH_VM_H

# include <sys/time.h>
# include <list.h>
# include <libft.h>
# include "utils.h"
# include "corewar_struct.h"
# include "process_struct.h"
# include "safe_malloc.h"
# include "corewar_define.h"
# include "execute_process.h"
# include "dump_memory.h"
# include "execute_loop.h"
# include "ins_fn.h"
# include "init_ncurses.h"
# include "quit_ncurses.h"
# include "input.h"
# include "update_player_info.h"
# include "update_vm_info.h"
# include "update_ins_info.h"
# include "display_winner.h"

typedef struct		s_loop_param
{
	struct timeval	a;
	struct timeval	b;
	t_input			input;
}					t_loop_param;

int					launch_vm(t_vm *vm);
int					init_vm(t_vm *vm);
int					init_launch_vm(t_vm *vm, t_loop_param *p,
						int *i, int *flag);

#endif
