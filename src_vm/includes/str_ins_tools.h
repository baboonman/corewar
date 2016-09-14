/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ins_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_INS_TOOLS_H
# define STR_INS_TOOLS_H

# include "op.h"
# include "corewar_struct.h"
# include "process_struct.h"
# include "ins_tools.h"
# include <libft.h>
# include "safe_malloc.h"

t_disp_ins	*get_str_ins(t_process *proc);

#endif
