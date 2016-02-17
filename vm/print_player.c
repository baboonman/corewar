#include "print_player.h"

int		print_player(t_vm *vm)
{
	int			i;
	t_player	*player;

	i = 0;
	while (i < vm->nb_players)
	{
		player = vm->players + i;
		ft_printf("Name: %s\nComment: %s\n",
				player->header.prog_name, player->header.comment);
		ft_printf("File size: %d\nBin size: %d\n",
				(int)player->size_bin, (int)player->header.prog_size);
		++i;
	}
	return (TRUE);
}
