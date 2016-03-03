#ifndef INS_FN_H
# define INS_FN_H

# include <unistd.h>
# include "op.h"
# include "corewar_struct.h"
# include "process_struct.h"
# include "mem_utils.h"
# include "safe_malloc.h"
# include <ft_printf.h>
# include <libft.h>
# define P_VAL_1 proc->curr_ins.param_val[0]
# define P_VAL_2 proc->curr_ins.param_val[1]
# define P_VAL_3 proc->curr_ins.param_val[2]
# define P_TYPE_1 proc->curr_ins.param_type[0]
# define P_TYPE_2 proc->curr_ins.param_type[1]
# define P_TYPE_3 proc->curr_ins.param_type[2]

void	ins_live(t_vm *vm, t_process *proc);

void	ins_aff(t_vm *vm, t_process *proc);
void	ins_and(t_vm *vm, t_process *proc);
void	ins_add(t_vm *vm, t_process *proc);
void	ins_xor(t_vm *vm, t_process *proc);
void	ins_ldi(t_vm *vm, t_process *proc);
void	ins_lldi(t_vm *vm, t_process *proc);
void	ins_fork(t_vm *vm, t_process *proc);
void	ins_lfork(t_vm *vm, t_process *proc);
#endif
