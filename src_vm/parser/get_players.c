/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_players.h"

static int		open_file(char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("Unable to open the file %s\n", file_name);
		return (-1);
	}
	return (fd);
}

static int		set_player_info(int fd, t_player *player,
		int player_nb, char *file_name)
{
	lseek(fd, 0, SEEK_SET);
	if (!read_part_file(fd, sizeof(t_header), &(player->header)))
	{
		ft_printf("Unable to read the file %s\n", file_name);
		return (FALSE);
	}
	player->header.prog_name[PROG_NAME_LENGTH] = '\0';
	player->header.comment[COMMENT_LENGTH] = '\0';
	player->header.magic = swap_uint32(player->header.magic);
	player->header.prog_size = swap_uint32(player->header.prog_size);
	player->nb = player_nb * -1;
	player->bin = safe_malloc(player->size_bin);
	player->is_alive = TRUE;
	lseek(fd, sizeof(t_header), SEEK_SET);
	if (!read_part_file(fd, player->size_bin - sizeof(t_header), player->bin))
	{
		ft_printf("File %s not valid\n", file_name);
		return (FALSE);
	}
	return (TRUE);
}

static int		test_player_validity(t_player *player, char *file_name)
{
	if (player->header.magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Magic invalid for %s\n", file_name);
		return (FALSE);
	}
	if (player->header.prog_size + sizeof(t_header) != player->size_bin)
	{
		ft_printf("Binary size invalid for %s\n", file_name);
		return (FALSE);
	}
	return (TRUE);
}

static int		get_player(char *file_name, int player_nb, t_player *player,
		int col)
{
	int		fd;
	off_t	off;

	if ((fd = open_file(file_name)) < 0)
		return (FALSE);
	if ((off = get_size(fd)) < 0)
		return (FALSE);
	if (!test_size(off, file_name))
		return (FALSE);
	player->size_bin = (size_t)off;
	if (!set_player_info(fd, player, player_nb, file_name))
		return (FALSE);
	player->color = col;
	if (!test_player_validity(player, file_name))
		return (FALSE);
	return (TRUE);
}

int				get_players(t_vm *vm)
{
	int		i;
	int		col;
	int		tot_players;

	i = 0;
	col = 1;
	tot_players = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->param.file_players[i])
		{
			if (!get_player(vm->param.file_players[i], i + 1,
						vm->players + tot_players, col))
				return (FALSE);
			++tot_players;
			col++;
		}
		i++;
	}
	if (tot_players <= 0)
		return (FALSE);
	vm->nb_players = tot_players;
	return (TRUE);
}
