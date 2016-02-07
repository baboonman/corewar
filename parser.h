#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include "op.h"
# include <ft_printf.h>
# include <libft.h>
# include <list.h>

# define T_COMMENT		1
# define T_NAME			2
# define SIZE_NAME_CMD	(sizeof(NAME_CMD_STRING) - 1)
# define SIZE_COMMENT_CMD (sizeof(COMMENT_CMD_STRING) - 1)

# define ERROR_LEXICAL 1
# define NO_ERROR 0

typedef struct		s_token_section
{
	int				type;
	char			*value;
}					t_token_section;

typedef struct		s_token_op
{
}					t_token_op;

int		parse_file(t_file *file);

#endif
