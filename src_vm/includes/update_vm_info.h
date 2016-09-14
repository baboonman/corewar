/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vm_info.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_VM_INFO_H
# define UPDATE_VM_INFO_H

# include "corewar_struct.h"
# include <ncurses.h>
# include <panel.h>
# include <libft.h>
# include "init_ncurses.h"

void	update_vm_info(t_vm *vm);

typedef WINDOW * t_win;

#endif
