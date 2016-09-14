/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_ncurses.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_NCURSES_H
# define QUIT_NCURSES_H

# include <stdlib.h>
# include <panel.h>
# include <ncurses.h>
# include <unistd.h>
# include "corewar_struct.h"

void		quit_ncurses(t_ncurses *ncurses);

#endif
