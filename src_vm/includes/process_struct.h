#ifndef PROCESS_STRUCT_H
# define PROCESS_STRUCT_H

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
	int						pc;
	t_ins					curr_ins;
	int						player_nb;
	int						nb_live;
}							t_process;

#endif
