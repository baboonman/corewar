#include "parser.h"

static t_token_section		*check_section(char *str, int *error)
{
	t_token_section	*token;
	char			*start;
	char			*end;
	char			*tmp;

	token = malloc(sizeof(t_token_section));
	if (!ft_strncmp(str, NAME_CMD_STRING, SIZE_NAME_CMD))
		token->type = T_NAME;
	else if (!ft_strncmp(str, COMMENT_CMD_STRING, SIZE_COMMENT_CMD))
		token->type = T_COMMENT;
	else
	{
		free(token);
		*error = NO_ERROR;
		return (NULL);
	}
	if (!(start = ft_strchr(str, '"'))
			|| !(end = ft_strchr(start + 1, '"'))
			|| (tmp = ft_strchr(end + 1, '"')))
	{
		*error = ERROR_LEXICAL;
		free(token);
		return (NULL);
	}
	token->value = malloc(sizeof(char) * (end - start + 1));
	ft_strncpy(token->value, start, end - start);
	token->value[end - start] = '\0';
	return (token);
}


static int					process_line(char *line, t_file *file)
{
	char				*trim;
	int					err;
	t_token_section		*section;

	trim = ft_strtrim(line);
	if ((section = check_section(trim, &err)))
	{
		ft_lstadd(&(file->list_section), ft_lstnew(section, sizeof(*section)));
	}
	else if (err != NO_ERROR)
	{
		ft_printf("ERROR BITCH\n");
	}
	free(trim);
	return(TRUE);	
}

static void					*print_token(void *data)
{
	t_token_section		*section;

	section = data;
	ft_printf("type: %d, val: %s\n", section->type, section->value);
	return (data);
}

int							parse_file(t_file *file)
{
	size_t		i;

	i = 0;
	while (i < file->nb_lines)
	{
		process_line(file->lines[i], file);
		i++;
	}
	ft_lstiter(file->list_section, print_token);
	return (TRUE);
}
