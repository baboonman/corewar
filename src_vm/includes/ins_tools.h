/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:19 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INS_TOOLS_H
# define INS_TOOLS_H

# include "corewar_struct.h"
# include "process_struct.h"
# include <libft.h>
# include "struct_op.h"

void	add_ins_line(t_ncurses *ncurses, t_disp_ins *line);
char	*get_proc_player_str(t_process *proc);
char	*get_reg_str(t_process *proc, int reg);
char	*get_itoa_space(int val);

#endif
