#ifndef COREWAR_STRUCT_H
# define COREWAR_STRUCT_H

# include "op.h"
# include <stddef.h>
# include <list.h>

typedef struct		s_player
{
	void			*bin;
	size_t			size_bin;
	t_header		header;
	int				nb;
	t_list			*lst_process;
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

typedef struct		s_vm
{
	t_player		players[MAX_PLAYERS];
	int				nb_players;
	void			*mem_space;
	t_param			param;
	void			*ins_function[16];
}					t_vm;

#endif
