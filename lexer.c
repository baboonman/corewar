#include "lexer.h"

static t_token_section		*check_section(char *str, t_error **error)
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
		return (NULL);
	}
	if (!(start = ft_strchr(str, '"'))
			|| !(end = ft_strchr(start + 1, '"'))
			|| (tmp = ft_strchr(end + 1, '"')))
	{
		*error = get_error(COM_ERR_QUOTE);
		free(token);
		return (NULL);
	}
	token->value = malloc(sizeof(char) * (end - start + 1));
	start++;
	ft_strncpy(token->value, start, end - start);
	token->value[end - start] = '\0';
	return (token);
}

static t_list				*get_last_elem(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static void					add_line(t_list *list, int line)
{
	while (list)
	{
		((t_token_op *)(list->content))->line = line;
		list = list->next;
	}
}

static int					process_line(char *line, t_file *file, int line_number)
{
	char				*trim;
	t_error				*err;
	t_token_section		*section;
	t_list				*end_op;

	end_op = get_last_elem(file->list_op);
	err = NULL;
	trim = ft_strtrim(line);
	if (!ft_strlen(trim))
		return (TRUE);
	if ((section = check_section(trim, &err)))
	{
		section->line = line_number;
		ft_lstadd(&(file->list_sections), ft_lstnew(section, sizeof(*section)));
	}
	else if (err)
	{
		err->line = line_number;
		ft_lstadd(&(file->list_errors), ft_lstnew(err, sizeof(err)));
	}
	else if ((check_op(trim, &err, &(file->list_op))))
	{
		if (end_op == NULL)
			add_line(file->list_op, line_number);
		else
			add_line(end_op->next, line_number);
	}
	else if (err)
	{
		err->line = line_number;
		ft_lstadd(&(file->list_errors), ft_lstnew(err, sizeof(err)));
	}
	else
	{
		err = get_error(INVALID_LINE);
		err->line = line_number;
		ft_lstadd(&(file->list_errors), ft_lstnew(err, sizeof(err)));
	}
	free(trim);
	return(TRUE);	
}

static void					*print_token(void *data)
{
	t_token_section		*section;

	section = data;
	ft_printf("type: %d, val: %s, line: %d\n", section->type, section->value, section->line);
	return (data);
}

static void					*print_op(void *data)
{
	t_token_op		*op;
	int				i;

	op = data;
	if (op->type == OP_TYPE_LABEL)
		ft_printf("type: label, label: %s, line: %d\n", op->label, op->line);
	else
	{
		i = 0;
		ft_printf("Type: %d, op: %d, line: %d", op->type, op->op, op->line);
		while (i < op->nb_param)
		{
			if (op->param_type[i] & T_LAB)
			{
				ft_printf(", p%d: type: %d(label), val: %s", i ,
						op->param_type[i] & (~T_LAB), op->param_lab[i]);
			}
			else
			{
				ft_printf(", p%d: type: %d, val: %d", i, op->param_type[i], op->param_val[i]);
			}
			i++;
		}
		ft_printf("\n");

	}
	return (data);
}

int							parse_file(t_file *file)
{
	size_t		i;

	i = 0;
	while (i < file->nb_lines)
	{
		process_line(file->lines[i], file, i + 1);
		i++;
	}
	if (file->list_errors)
		ft_lstiter(file->list_errors, print_error);
	else
	{
		ft_printf("Section:\n");
		ft_lstiter(file->list_sections, print_token);
		ft_printf("Op:\n");
		ft_lstiter(file->list_op, print_op);
	}
	return (TRUE);
}
