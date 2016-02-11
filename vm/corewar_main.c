#include "corewar_main.h"

int		main(int argc, char **argv)
{
	t_vm		*vm;

	vm = malloc(sizeof(t_vm));
	if (argc < 2)
		return (1);
	if (!get_players(vm, argv + 1, 1))
	{
		free(vm);
		return (1);
	}
	print_player(vm->players);
	return (0);
}
