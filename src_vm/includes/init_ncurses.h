/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:19 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_NCURSES_H
# define INIT_NCURSES_H

# include <stdlib.h>
# include <panel.h>
# include <ncurses.h>
# include <unistd.h>
# include "corewar_struct.h"
# include "init_mem.h"
# include "display_utils.h"

# include "op.h"

# define MEM_LINE_SIZE 64

# define MEM_WIDTH (MEM_LINE_SIZE * 3 + 2)
# define MEM_HEIGHT (MEM_SIZE / MEM_LINE_SIZE)

# define MEM_BORD_WIDTH MEM_WIDTH + 2
# define MEM_BORD_HEIGHT MEM_HEIGHT + 2

# define TMP_WIDTH (60)
# define TMP_HEIGHT (MEM_HEIGHT)
# define TMP_BORD_WIDTH (TMP_WIDTH + 3)
# define TMP_BORD_HEIGHT (TMP_HEIGHT + 2)

# define INS_WIDTH TMP_WIDTH
# define GLOB_HEIGHT 10
# define INS_HEIGHT (TMP_HEIGHT - GLOB_HEIGHT)

# define PLAYERS_INFO_HEIGHT 2
# define PLAYERS_INFO_WIDTH (MEM_BORD_WIDTH + INS_WIDTH)

# define PLAYERS_INFO_BORD_HEIGHT PLAYERS_INFO_HEIGHT + 2
# define PLAYERS_INFO_BORD_WIDTH PLAYERS_INFO_WIDTH + 2

# define PLAYERS_POS_X 0
# define PLAYERS_POS_Y 0

# define MEM_POS_X PLAYERS_INFO_HEIGHT
# define MEM_POS_Y 0

# define WIN_MEM 0
# define WIN_INFO 1
# define WIN_INS 2
# define WIN_GLOB_INF 3

int		init_ncurses(t_ncurses *ncurses, t_vm *vm);
int		set_color(void);

#endif
