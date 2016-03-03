#ifndef STRUCT_OP_H
# define STRUCT_OP_H

typedef struct				s_op
{
	char					*name_op;
	int						nb_param;
	t_arg_type				param_type[3];
	int						op_code;
	int						nb_cycle;
	char					*description;
	int						has_opc;
	int						has_idx;
	int						mod_carry;

}							t_op;

t_op						g_op_tab[17];

#endif
