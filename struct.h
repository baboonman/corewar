#ifndef STRUCT_H
# define STRUCT_H

# include <stddef.h>
# include <list.h>

typedef struct				s_file
{
	int						fd;
	char					**lines;
	size_t					nb_lines;
	size_t					nb_allocated_lines;
	t_list					*list_section;
}							t_file;

# define TRUE 1
# define FALSE 0

#endif
