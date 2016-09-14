/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_op.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_OP_H
# define PROCESS_OP_H

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "define_error.h"
# include "utils.h"
# include "process_op_utils.h"
# include "safe_malloc.h"

int					process_op(char *str, t_error **err, t_list **token_op);

#endif
