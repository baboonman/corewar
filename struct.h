#ifndef STRUCT_H
# define STRUCT_H

# include <stddef.h>
# include <list.h>

# define MAX_SIZE_ERROR	255

typedef struct				s_file
{
	int						fd;
	char					**lines;
	size_t					nb_lines;
	size_t					nb_allocated_lines;
	t_list					*list_sections;
	t_list					*list_errors;
}							t_file;

typedef struct				s_error
{
	int						line;
	char					description[MAX_SIZE_ERROR + 1];
}							t_error;

# define TRUE 1
# define FALSE 0

#endif
