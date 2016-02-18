#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <unistd.h>

# include <ft_printf.h>
# include "lexer.h"
# include "struct.h"
# include "op.h"
# include "swap_bytes.h"

typedef struct			s_label_param
{
	size_t				offset;
	size_t				size;
	size_t				pc;
	char				*name;
}						t_label_param;

typedef struct			s_label_offset
{
	char				*name;
	size_t				offset;
}						t_label_offset;

typedef struct			s_bin_data
{
	char				*bin_file;
	t_header			*header;
	int					size;
	t_label_param		**pl;
	size_t				pl_size;
	t_label_offset		**lo;
	size_t				lo_size;
}						t_bin_data;

int						process_file(t_file *file);

#endif
