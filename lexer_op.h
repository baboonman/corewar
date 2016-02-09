#ifndef LEXER_OP_H
# define LEXER_OP_H

# include "struct.h"
# include "op.h"

# define UNVALID_CHAR_LABEL "Label has invalid char"

t_token_op			*check_op(char *str, t_error **error);

#endif
