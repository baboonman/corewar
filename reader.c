#include "reader.h"

static int			realloc_lines(t_file *file)
{
	file->nb_allocated_lines += SIZE_BUFF_LINE;
	if (!(file->lines = realloc(file->lines, sizeof(char *) * file->nb_allocated_lines)))
		return (FALSE);
	return TRUE;
}

static int			get_lines(t_file *file)
{
	if (!realloc_lines(file))
		return (FALSE);
	while (get_next_line(file->fd, file->lines + file->nb_lines) > 0)
	{
		file->nb_lines++;
		if (file->nb_lines >= file->nb_allocated_lines)
		{
			if (!realloc_lines(file))
				return (FALSE);
		}
	}
	return (TRUE);
}

void				print_file(t_file *file)
{
	size_t		i;

	i = 0;
	while (i < file->nb_lines)
		ft_printf("%s\n", file->lines[i++]);
}

t_file				*read_file(char *name)
{
	t_file		*file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	ft_bzero(file, sizeof(t_file));
	if ((file->fd = open(name, O_RDONLY)) < 0)
	{
		ft_printf("Unable to open the file %s\n", name);
		return (NULL);
	}
	file->lines = NULL;
	file->nb_allocated_lines = 0;
	file->nb_lines = 0;
	if (!get_lines(file))
		ft_printf("Something wrong append\n");
	close(file->fd);
//	print_file(file);
	return (file);
}
