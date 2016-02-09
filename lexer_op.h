#ifndef LEXER_OP_H
# define LEXER_OP_H

# include <libft.h>

# include "struct.h"
# include "op.h"
# include "error_util.h"

# define UNVALID_CHAR_LABEL "Label has invalid char"
# define UNVALID_NO_PARAM "There is no parameter"
# define UNVALID_NO_OPCODE "Opcode not found"

int			check_op(char *str, t_error **err, t_list **token_op);

#endif
