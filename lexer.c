#include "lexer.h"

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

static void					manage_op_lex(char *trim, t_file *file,
		int line_number)
{
	t_list				*end_op;
	t_error				*err;

	err = NULL;
	end_op = get_last_elem(file->list_op);
	if ((check_op(trim, &err, &(file->list_op))))
	{
		if (end_op == NULL)
			add_line(file->list_op, line_number);
		else
			add_line(end_op->next, line_number);
		return ;
	}
	if (err)
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
}

static void					process_line(char *line, t_file *file,
		int line_number)
{
	char				*trim;
	t_error				*err;
	t_token_section		*section;

	err = NULL;
	trim = ft_strtrim(line);
	if (!ft_strlen(trim))
	{
		free(trim);
		return ;
	}
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
	else
		manage_op_lex(trim, file, line_number);
	free(trim);
	return ;
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
	ft_lstiter(file->list_errors, print_error);
	if (file->list_errors)
		return (FALSE);
	ft_printf("section:\n");
	ft_lstiter(file->list_sections, print_token);
	ft_printf("\nop:\n");
	ft_lstiter(file->list_op, print_op);
	return (TRUE);
}
