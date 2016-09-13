#ifndef COREWAR_STRUCT_H
# define COREWAR_STRUCT_H

# include "op.h"
# include <stddef.h>
# include <list.h>
# include <ncurses.h>
# include <panel.h>

# define NB_INS_DISPLAY 40

typedef struct		s_player
{
	void			*bin;
	size_t			size_bin;
	t_header		header;
	int				nb;
	int				nb_live;
	int				is_alive;
	int				color;
	int				die_at;
}					t_player;

typedef struct		s_param
{
	int				is_dump;
	int				is_ncurses;
	int				nb_cycle_dump;
	char			*file_players[MAX_PLAYERS];
	int				player_nb[MAX_PLAYERS];
	int				nb_players;
	int				verbose;
}					t_param;

typedef struct		s_cycle_die
{
	int				to_die;
	int				step;
	int				nb_cycle;
	int				tot_live;
}					t_cycle_die;

typedef struct		s_disp_ins
{
	int				player_id;
	char			*str;
}					t_disp_ins;

typedef struct		s_ncurses
{
	WINDOW			*window[4];
	WINDOW			*border[3];
	WINDOW			*winner[2];
	PANEL			*panel[7];
	t_disp_ins		*lst_ins[NB_INS_DISPLAY];
	int				pos;
	int				size;
}					t_ncurses;

typedef struct		s_vm
{
	t_player		players[MAX_PLAYERS];
	t_list			*lst_process;
	int				nb_players;
	void			*mem_space;
	uint8_t			*mem_space_col;
	t_param			param;
	void			*ins_function[16];
	t_cycle_die		cycle_die;
	int				nb_proc;
	t_ncurses		ncurses;
	int				tot_cycle;
	int				fps;
}					t_vm;

#endif
