#ifndef PROCESS_STRUCT
# define PROCESS_STRUCT

# include "op.h"

typedef struct				s_ins
{
	int						opcode;
	size_t					size;
	int						param_val[3];
	t_arg_type				param_type[3];
}							t_ins;

typedef struct				s_process
{
	int						reg[REG_NUMBER];
	int						carry;
	int						number_cycles;
	size_t					pc;
	t_ins					curr_ins;
}							t_process;

#endif
