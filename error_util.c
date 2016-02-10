#include "error_util.h"

t_error		*get_error(char *description)
{
	t_error		*err;

	err = malloc(sizeof(t_error));
	ft_bzero(err, sizeof(t_error));
	ft_strncpy(err->description, description, MAX_SIZE_ERROR);
	return (err);
}

void		*print_error(void *data)
{
	t_error	*err;

	err = data;
	ft_printf("Syntax error: line: %d, err: %s\n", err->line, err->description);
	return (data);
}

int			ret_error(char *description)
{
	ft_printf("Error: %s\n", description);
	return (FALSE);
}
