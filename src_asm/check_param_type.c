#include "check_param_type.h"

int		check_param_type(t_token_op *token, t_arg_type *mask, t_error **err)
{
	int	i;

	i = 0;
	while (i < token->nb_param)
	{
		if (!(token->param_type[i] & mask[i]))
			return (set_error_ret(err, INVALID_PARAM, token->line));
		i++;
	}
	return (TRUE);
}
