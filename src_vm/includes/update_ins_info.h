/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ins_info.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_INS_INFO_H
# define UPDATE_INS_INFO_H

# include "corewar_struct.h"
# include <ncurses.h>
# include <panel.h>
# include <libft.h>
# include "init_ncurses.h"

void				update_ins_info(t_vm *vm);

typedef struct		s_ins_param
{
	WINDOW			*win;
	int				max_x;
	int				max_y;
}					t_ins_param;

#endif
