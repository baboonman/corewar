#ifndef EXECUTE_PROCESS_H
# define EXECUTE_PROCESS_H

# include <stddef.h>
# include "process_struct.h"
# include "corewar_struct.h"
# include "safe_malloc.h"
# include "struct.h"
# include "libft.h"
# include "mem_utils.h"
# include "display_utils.h"
# include "ins_tools.h"

# include <unistd.h>
# include <stdlib.h>

int				execute_process(t_process *proc, t_vm *vm);
t_disp_ins		*get_str_invalid(t_process *proc);

#endif
