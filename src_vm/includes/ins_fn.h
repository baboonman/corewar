#ifndef INS_FN_H
# define INS_FN_H

# include "op.h"
# include "corewar_struct.h"
# include "process_struct.h"
# include "mem_utils.h"
# include <ft_printf.h>

void	ins_live(t_vm *vm, t_process *proc);
void	ins_ld(t_vm *vm, t_process *proc);

#endif
