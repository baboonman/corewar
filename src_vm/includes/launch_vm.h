#ifndef LAUNCH_VM_H
# define LAUNCH_VM_H

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

int			launch_vm(t_vm *vm);

#endif
