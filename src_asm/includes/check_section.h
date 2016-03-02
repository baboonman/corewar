#ifndef CHECK_SECTION_H
# define CHECK_SECTION_H

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "lexer_op.h"

# define T_COMMENT		1
# define T_NAME			2

# define SIZE_NAME_CMD	(sizeof(NAME_CMD_STRING) - 1)
# define SIZE_COMMENT_CMD (sizeof(COMMENT_CMD_STRING) - 1)

t_token_section				*check_section(char *str, t_error **error,
		size_t *line, t_file *file);
char						*get_str(size_t *line, t_file *file, char *start);

#endif
