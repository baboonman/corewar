#ifndef COREWAR_STRUCT_H
# define COREWAR_STRUCT_H

# include "../op.h"
# include <stddef.h>

typedef struct		s_player
{
	void			*bin;
	size_t			size_bin;
	t_header		header;
}					t_player;

typedef struct		s_param
{
	int				is_dump;
	int				nb_cycle_dump;
	char			**file_players;
	int				nb_players;
}					t_param;

typedef struct		s_vm
{
	t_player		players[MAX_PLAYERS];
	int				nb_players;
	t_param			param;
}					t_vm;

#endif
