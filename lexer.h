#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "lexer_op.h"
# include <ft_printf.h>
# include <libft.h>
# include <list.h>

# define T_COMMENT		1
# define T_NAME			2
# define SIZE_NAME_CMD	(sizeof(NAME_CMD_STRING) - 1)
# define SIZE_COMMENT_CMD (sizeof(COMMENT_CMD_STRING) - 1)

# define ERROR_LEXICAL 1
# define NO_ERROR 0

int		parse_file(t_file *file);

#endif
