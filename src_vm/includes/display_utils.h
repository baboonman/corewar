/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:19 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_UTILS_H
# define DISPLAY_UTILS_H

# include "init_ncurses.h"
# include "process_struct.h"
# include "mem_utils.h"

int				find_player_by_nb_player(t_vm *vm, int player_nb);
int				find_player(t_vm *vm, t_process *proc);
void			display_mem(t_vm *vm, int size, int off, int player_col);
void			print_cursor(t_vm *vm, int off, int on);
void			refresh_mem_display(t_vm *vm);

#endif
