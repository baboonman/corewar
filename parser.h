#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <unistd.h>

# include <ft_printf.h>
# include "lexer.h"
# include "struct.h"
# include "op.h"
# include "swap_bytes.h"

typedef struct			s_bin_offset
{
	char				*offset;
	int					size;
}						t_bin_offset;

typedef struct			s_bin_data
{
	char				*bin_file;
	t_header			*header;
	int					offset;
	int					size;
}						t_bin_data;

typedef struct			s_param_label
{
	size_t				param_offset;
	size_t				param_size;
	size_t				PC;
	char				*name;
}						t_param_label;

typedef struct			s_label_offset
{
	char				*label_name;
	size_t				label_offset;
}						t_label_offset;

int						process_file(t_file* file);

#endif
