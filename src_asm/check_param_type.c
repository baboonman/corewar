/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:48:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
