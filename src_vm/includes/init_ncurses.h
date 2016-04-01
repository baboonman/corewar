#ifndef INIT_NCURSES_H
# define INIT_NCURSES_H

# include <stdlib.h>
# include <panel.h>
# include <ncurses.h>
# include <unistd.h>
# include "corewar_struct.h"
# include "init_mem.h"

# include "op.h"

# define MEM_LINE_SIZE 64

# define MEM_WIDTH (MEM_LINE_SIZE * 3 + 2)
# define MEM_HEIGHT (MEM_SIZE / MEM_LINE_SIZE)

# define MEM_BORD_WIDTH MEM_WIDTH + 2
# define MEM_BORD_HEIGHT MEM_HEIGHT + 2

# define INS_WIDTH (40)
# define INS_HEIGHT (MEM_HEIGHT - 2)
# define INS_BORD_WIDTH (INS_WIDTH + 3)
# define INS_BORD_HEIGHT (INS_HEIGHT + 2)

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

int		init_ncurses(t_ncurses *ncurses, t_vm *vm);

#endif
