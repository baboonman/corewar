#ifndef CHECK_PARAM_TYPE_H
# define CHECK_PARAM_TYPE_H

# include "struct.h"
# include "error_util.h"
# include "define_error.h"

int		check_param_type(t_token_op *token, t_arg_type *mask, t_error **err);

#endif
