#ifndef LEXER_OP_H
# define LEXER_OP_H

# include <libft.h>

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "process_op.h"
# include "define_error.h"

int			check_op(char *str, t_error **err, t_list **token_op);

#endif
