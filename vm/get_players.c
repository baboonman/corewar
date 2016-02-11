#include "get_players.h"

static int		get_player(char *file_name, t_player *player)
{
	int		fd;
	off_t	off;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("Unable to open the file %s\n", file_name);
		return (FALSE);
	}
	if ((off = lseek(fd, 0, SEEK_END)) < 0)
	{
		ft_printf("Something wrong append\n");
		return (FALSE);
	}
	if ((unsigned int)off < sizeof(t_header))
	{
		ft_printf("The file %s is too small\n", file_name);
		return (FALSE);
	}
	player->size_bin = (size_t)off;
	lseek(fd, 0, SEEK_SET);
	if (!read_part_file(fd, off, &(player->header)))
	{
		ft_printf("Unable to read the file %s\n", file_name);
		return (FALSE);
	}
	player->header.prog_name[PROG_NAME_LENGTH] = '\0';
	player->header.comment[COMMENT_LENGTH] = '\0';
	player->header.magic = swap_uint32(player->header.magic);
	player->header.prog_size = swap_uint32(player->header.prog_size);
	if (player->header.magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Magic unvalid\n");
		return (FALSE);
	}
	if (player->header.prog_size + sizeof(t_header) != player->size_bin)
	{
		ft_printf("Binary size unvalid\n");
		return (FALSE);
	}
	return (TRUE);
}

int				get_players(t_vm *vm, char **file_players, int nb_players)
{
	int		i;

	i = 0;
	while (i < nb_players)
	{
		if (!get_player(file_players[i], vm->players + i))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
