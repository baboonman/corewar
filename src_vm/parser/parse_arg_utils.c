#include "parse_arg.h"

int		parse_ncurses(char **av, t_param *param)
{
	if (ft_strcmp(av[0], "-nc"))
		return (FALSE);
	param->is_ncurses = TRUE;
	return (TRUE);
}

int		parse_verbose(char **av, t_param *param)
{
	if (ft_strcmp(av[0], "-v"))
		return (FALSE);
	param->verbose = TRUE;
	return (TRUE);
}

off_t	get_size(int fd)
{
	off_t		off;

	if ((off = lseek(fd, 0, SEEK_END)) < 0)
	{
		ft_printf("Something wrong append (lseek fail)\n");
		return (-1);
	}
	return (off);
}

int		test_size(off_t off, char *name)
{
	if ((unsigned int)off < sizeof(t_header))
	{
		ft_printf("The file %s is too small\n", name);
		return (FALSE);
	}
	return (TRUE);
}
