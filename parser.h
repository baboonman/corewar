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
	t_bin_offset		prog_size;
}						t_bin_data;

int						process_file(t_file* file);

#endif
