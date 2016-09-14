/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:19 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:31 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_ext.h"

int		is_cor(char *filename)
{
	char	*ext;

	if (!(ext = ft_strrchr(filename, '.')))
		return (FALSE);
	return (!ft_strcmp(ext, ".cor"));
}

int		check_ext(t_param *param)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (param->file_players[i]
				&& !is_cor(param->file_players[i]))
		{
			ft_printf("Champ file must be .cor\n");
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}

void	kill_player(t_vm *vm, t_player *player)
{
	player->is_alive = FALSE;
	player->die_at = vm->tot_cycle;
	if (!vm->param.is_ncurses)
		ft_printf("player: %d, %s die\n", player->nb, player->header.prog_name);
	player->nb_live = 0;
}
