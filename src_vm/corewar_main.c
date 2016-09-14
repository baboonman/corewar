/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:19 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_printf("%s  [-dump nbr_cycles] [[-n number] champion1.cor] ...\n",
				argv[0]);
		return (1);
	}
	if (!get_players(vm))
	{
		free(vm);
		return (1);
	}
	if (vm->param.verbose)
		print_player(vm);
	launch_vm(vm);
	free(vm);
	return (0);
}
