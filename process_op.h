#ifndef PROCESS_OP_H
# define PROCESS_OP_H

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "define_error.h"

int					process_op(char *str, t_error **err, t_list **token_op);

#endif
