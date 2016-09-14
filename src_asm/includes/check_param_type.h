/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_type.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:48:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_PARAM_TYPE_H
# define CHECK_PARAM_TYPE_H

# include "struct.h"
# include "error_util.h"
# include "define_error.h"

int		check_param_type(t_token_op *token, t_arg_type *mask, t_error **err);

#endif
