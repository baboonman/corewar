#include "check_section.h"

static int					test_size(size_t size, int type)
{
	if (type == T_COMMENT)
		return (size <= COMMENT_LENGTH);
	if (type == T_NAME)
		return (size <= PROG_NAME_LENGTH);
	return (FALSE);
}

static int					check_error(char *str, t_error **error,
		t_token_section *token)
{
	char			*start;
	char			*end;
	char			*tmp;

	if (!(start = ft_strchr(str, '"'))
			|| !(end = ft_strchr(start + 1, '"'))
			|| (tmp = ft_strchr(end + 1, '"')))
	{
		*error = get_error(COM_ERR_QUOTE);
		return (FALSE);
	}
	start++;
	if (!test_size(end - start, token->type))
	{
		*error = get_error(COM_LENGTH);
		return (FALSE);
	}
	token->value = malloc(sizeof(char) * (end - start + 1));
	ft_strncpy(token->value, start, end - start);
	token->value[end - start] = '\0';
	return (TRUE);
}

t_token_section				*check_section(char *str, t_error **error)
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
	if (!check_error(str, error, token))
	{
		free(token);
		return (NULL);
	}
	return (token);
}
