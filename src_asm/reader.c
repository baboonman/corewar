#include "reader.h"

static int			realloc_lines(t_file *file)
{
	file->nb_allocated_lines += SIZE_BUFF_LINE;
	if (!(file->lines = realloc(file->lines,
					sizeof(char *) * file->nb_allocated_lines)))
		return (FALSE);
	return (TRUE);
}

static void			remove_comment(char *str)
{
	char	*pos;

	pos = ft_strchr(str, COMMENT_CHAR);
	if (!pos)
		return ;
	*pos = '\0';
}

static int			get_lines(t_file *file)
{
	if (!realloc_lines(file))
		return (FALSE);
	while (get_next_line(file->fd, file->lines + file->nb_lines) > 0)
	{
		remove_comment(file->lines[file->nb_lines]);
		file->nb_lines++;
		if (file->nb_lines >= file->nb_allocated_lines)
		{
			if (!realloc_lines(file))
				return (FALSE);
		}
	}
	return (TRUE);
}

static char			*get_cor_name(char *name)
{
	int		i;
	char	*cor_name;

	i = ft_strlen(name);
	if (i < 3)
		return (NULL);
	if (ft_strncmp(name + i - 2, ".s", 2))
		return (NULL);
	cor_name = ft_strnew(i + 2);
	ft_strcpy(cor_name, name);
	ft_strcpy(cor_name + i - 2, ".cor");
	return (cor_name);
}

t_file				*read_file(char *name)
{
	t_file		*file;

	file = safe_malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	ft_bzero(file, sizeof(t_file));
	file->file_name = ft_strdup(name);
	if (!(file->cor_name = get_cor_name(name)))
	{
		ft_printf("Filename unvalid\n");
		return (NULL);
	}
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
	return (file);
}
