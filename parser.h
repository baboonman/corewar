#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <unistd.h>

# include <ft_printf.h>
# include "lexer.h"
# include "struct.h"
# include "op.h"
# include "swap_bytes.h"

int				process_file(t_file* file);

#endif
