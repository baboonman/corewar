#include "print_player.h"

int		print_player(t_player *player)
{
	ft_printf("Name: %s\nComment: %s\n",
			player->header.prog_name, player->header.comment);
	ft_printf("File size: %d\nBin size: %d\n",
			(int)player->size_bin, (int)player->header.prog_size);
	return (TRUE);
}
