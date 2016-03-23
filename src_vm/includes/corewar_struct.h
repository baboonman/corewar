#ifndef COREWAR_STRUCT_H
# define COREWAR_STRUCT_H

# include "op.h"
# include <stddef.h>
# include <list.h>
# include <ncurses.h>
# include <panel.h>

typedef struct		s_player
{
	void			*bin;
	size_t			size_bin;
	t_header		header;
	int				nb;
	//t_list			*lst_process;
	int				nb_live;
	int				is_alive;
}					t_player;

typedef struct		s_param
{
	int				is_dump;
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
}					t_cycle_die;

typedef struct		s_ncurses
{
	WINDOW			*window[3];
	WINDOW			*border[3];
	PANEL			*panel[6];
}					t_ncurses;

typedef struct		s_vm
{
	t_player		players[MAX_PLAYERS];
	t_list			*lst_process;
	int				nb_players;
	void			*mem_space;
	t_param			param;
	void			*ins_function[16];
	t_cycle_die		cycle_die;
	int				nb_proc;
	t_ncurses		ncurses;
}					t_vm;

#endif
