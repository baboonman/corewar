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

static off_t	get_size(int fd)
{
	off_t		off;

	if ((off = lseek(fd, 0, SEEK_END)) < 0)
	{
		ft_printf("Something wrong append (lseek fail)\n");
		return (-1);
	}
	return (off);
}

static int		test_size(off_t off, char *name)
{
	if ((unsigned int)off < sizeof(t_header))
	{
		ft_printf("The file %s is too small\n", name);
		return (FALSE);
	}
	return (TRUE);
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
	player->nb = player_nb;
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

static int		get_player(char *file_name, int player_nb, t_player *player)
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
	if (!test_player_validity(player, file_name))
		return (FALSE);
	return (TRUE);
}

int				get_players(t_vm *vm)
{
	int		i;
	int		tot_players;

	i = 0;
	tot_players = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->param.file_players[i])
		{
			if (!get_player(vm->param.file_players[i], i + 1,
						vm->players + tot_players))
				return (FALSE);
			++tot_players;
		}
		i++;
	}
	vm->nb_players = tot_players;
	return (TRUE);
}