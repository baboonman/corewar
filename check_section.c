#include "check_section.h"

static int					test_size(size_t size, int type)
{
	if (type == T_COMMENT)
		return (size <= COMMENT_LENGTH);
	if (type == T_NAME)
		return (size <= PROG_NAME_LENGTH);
	return (FALSE);
}

static void					*ft_realloc(void *p, size_t size)
{
	void	*tmp_p;

	tmp_p = NULL;
	tmp_p = malloc(sizeof(char) * size);
	ft_bzero(tmp_p, size);
	if (p)
	{
		ft_strcpy(tmp_p, p);
		free(p);
	}
	return (tmp_p);
}

static char					*get_str(size_t *line, t_file *file, char *start)
{
	char		*res;
	char		*end;
	size_t		size;
	char		*tmp_line;
	size_t		tmp;

	res = ft_realloc(NULL, sizeof(char));
	size = 1;
	tmp_line = NULL;
	while (*line < file->nb_lines)
	{
		if (!tmp_line)
			tmp_line = start;
		else
			tmp_line = file->lines[*line];
		if ((end = ft_strchr(tmp_line, '"')))
		{
			if (ft_strchr(end + 1, '"'))
			{
				free(res);
				return (NULL);
			}
			tmp = size;
			size += end - tmp_line;
			if (!(res = ft_realloc(res, sizeof(char) * (size + 1))))
				return (NULL);
			return (ft_strncat(res, tmp_line, end - tmp_line));
		}
		size += ft_strlen(tmp_line) + 1;
		if (!(res = ft_realloc(res, sizeof(char) * (size + 1))))
			return (NULL);
		ft_strcat(res, tmp_line);
		res[size - 2] = '\n';
		*line += 1;
	}
	free(res);
	return (NULL);
}

static int					check_error(t_error **error, t_token_section *token,
		size_t *line, t_file *file)
{
	char			*str;
	char			*start;

	str = NULL;
	if (!(start = ft_strchr(file->lines[*line], '"'))
		|| !(str = get_str(line, file, start + 1)))
	{
		*error = get_error(COM_ERR_QUOTE);
		return (FALSE);
	}
	if (!test_size(ft_strlen(str), token->type))
	{
		free(str);
		*error = get_error(COM_LENGTH);
		return (FALSE);
	}
	token->value = str;
	return (TRUE);
}

t_token_section				*check_section(char *str, t_error **error,
		size_t *line, t_file *file)
{
	t_token_section	*token;

	token = malloc(sizeof(t_token_section));
	if (!ft_strncmp(str, NAME_CMD_STRING, SIZE_NAME_CMD))
		token->type = T_NAME;
	else if (!ft_strncmp(str, COMMENT_CMD_STRING, SIZE_COMMENT_CMD))
		token->type = T_COMMENT;
	else
	{
		free(token);
		return (NULL);
	}
	if (!check_error(error, token, line, file))
	{
		free(token);
		return (NULL);
	}
	return (token);
}
