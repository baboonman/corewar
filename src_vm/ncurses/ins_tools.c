#include "ins_tools.h"

void	add_ins_line(t_ncurses *ncurses, t_disp_ins *line)
{
	if (ncurses->lst_ins[ncurses->pos])
	{
		free(ncurses->lst_ins[ncurses->pos]->str);
		free(ncurses->lst_ins[ncurses->pos]);
	}
	ncurses->lst_ins[ncurses->pos] = line;
	if (ncurses->size < NB_INS_DISPLAY)
		ncurses->size++;
	ncurses->pos = (ncurses->pos + 1) % NB_INS_DISPLAY;
}

char	*get_reg_str(t_process *proc, int reg)
{
	char	*res;
	char	*nb;
	char	*val;

	nb = ft_itoa(reg);
	val = ft_itoa(proc->reg[reg - 1]);
	res = ft_strnew(ft_strlen(nb) + ft_strlen(val) + 4);
	ft_strcpy(res, "r");
	ft_strcat(res, nb);
	ft_strcat(res, "(");
	ft_strcat(res, val);
	ft_strcat(res, ") ");
	return (res);
}


char	*get_itoa_space(int val)
{
	char	*res;
	char	*tmp;

	tmp = ft_itoa(val);
	res = ft_strnew(ft_strlen(tmp) + 1);
	ft_strcpy(res, tmp);
	ft_strcat(res, " ");
	free(tmp);
	return (res);
}

char	*get_proc_player_str(t_process *proc)
{
	char	*player_nb;
	char	*proc_nb;
	char	*res;

	if (!(player_nb = ft_itoa(proc->player_nb)))
		return (NULL);
	if (!(proc_nb = ft_itoa(proc->proc_nb)))
	{
		free(player_nb);
		return (NULL);
	}
	if (!(res = ft_strnew(ft_strlen(player_nb) + ft_strlen(proc_nb) + 4)))
	{
		free(proc_nb);
		free(player_nb);
		return (NULL);
	}
	ft_strcpy(res, player_nb);
	ft_strcat(res, " (");
	ft_strcat(res, proc_nb);
	ft_strcat(res, ") ");
	free(player_nb);
	free(proc_nb);
	return (res);
}
