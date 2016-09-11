#ifndef INPUT_H
# define INPUT_H

typedef struct		s_input
{
	int				tps;
	int				pause;
}					t_input;

void				init_input(t_input *param);
void				get_input(t_input *param);

#endif
