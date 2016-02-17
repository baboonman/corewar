#include "corewar_main.h"

int		main(int argc, char **argv)
{
	t_vm		*vm;

	vm = malloc(sizeof(t_vm));
	ft_bzero(vm, sizeof(t_vm));
	if (argc < 2 || !parse_arg(&(vm->param), argc - 1, argv + 1))
	{
		if (argc <= 0)
			return (1);
		ft_printf("%s  [-dump nbr_cycles] [[-n number] champion1.cor] ...\n", argv[0]);
		return (1);
	}
	if (!get_players(vm))
	{
		free(vm);
		return (1);
	}
	print_player(vm);
	free(vm);
	return (0);
}
