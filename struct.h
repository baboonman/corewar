#ifndef STRUCT_H
# define STRUCT_H

# include <stddef.h>
# include <list.h>

# define MAX_SIZE_ERROR	255

# define OP_TYPE_LABEL	0
# define OP_TYPE_OP		0

typedef struct				s_token_section
{
	int						type;
	char					*value;
}							t_token_section;

typedef struct				s_token_op
{
	int						type;
	int						op;
	int						param_type[3];
	int						nb_param;
	int						param_val[3];
	char					*param_lab[3];
	char					*label;
}							t_token_op;

typedef struct				s_file
{
	int						fd;
	char					**lines;
	size_t					nb_lines;
	size_t					nb_allocated_lines;
	t_list					*list_sections;
	t_list					*list_errors;
	t_list					*list_op;
}							t_file;

typedef struct				s_error
{
	int						line;
	char					description[MAX_SIZE_ERROR + 1];
}							t_error;

typedef struct				s_op
{
	char					*name_op;
	int						nb_param;
	int						param_type[3];
	int						op_code;
	int						nb_cycle;
	char					*description;
	int						has_opc;
	int						has_idx;

}							t_op;

t_op					op_tab[17];

# define TRUE 1
# define FALSE 0

#endif
