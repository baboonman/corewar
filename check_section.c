#include "check_section.h"

static int					test_size(size_t size, int type)
{
	if (type == T_COMMENT)
		return (size <= COMMENT_LENGTH);
	if (type == T_NAME)
		return (size <= PROG_NAME_LENGTH);
	return (FALSE);
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
