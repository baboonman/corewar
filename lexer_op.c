#include "lexer_op.h"

t_token_op	*check_label(char *str, size_t size, t_error **err)
{
	size_t		i;
	t_token_op	*op;

	i = 0;
	while (i < size)
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
		{
			*err = get_error(UNVALID_CHAR_LABEL);
			return (NULL);
		}
		i++;
	}
	op = malloc(sizeof(t_token_op));
	op->type = OP_TYPE_LABEL;
	op->label = malloc(size + 1);
	ft_strncpy(op->label, str, size);
	op->label[size] = '\0';
	return (op);
}

static int	process_label_op(char *str, t_error **err, t_list **token_op,
		size_t label_offset)
{
	t_token_op	*op;

	op = check_label(str, label_offset, err);
	return (TRUE);
}

static int	process_label(char *str, t_error **err, t_list **token_op, size_t size)
{
	t_token_op	*op;

	if (str[size - 1] == LABEL_CHAR)
	{
		if ((op = check_label(str, size - 1, err)))
		{
			ft_lstadd(token_op, ft_lstnew(op, sizeof(*op)));
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (TRUE);
}


static size_t		get_param_limit(char *p)
{
	char		*end;

	end = ft_strchr(p, SEPARATOR_CHAR);
	if (end)
		return (end - p);
	return ft_strlen(p);
}

static int	process_opcode(t_op *opcode, char *str_param, t_error **err)
{
	t_token_op		*op;
	int				type;

	op = malloc(sizeof(t_token_op));
	
	return (FALSE);
}

static int	process_op(char *str, t_error **err, t_list **token_op)
{
	char	*next;
	int		i;
	size_t	size;
	int		ret;

	next = ft_strchr(str, ' ');
	if (next == NULL)
	{
		*err = get_error(UNVALID_NO_PARAM);
		return (FALSE);
	}
	size = next - str;
	i = 0;
	while (op_tab[i].name_op)
	{
		if (ft_strlen(op_tab[i].name_op) != size)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(op_tab[i].name_op, str, size) != 0)
		{
			i++;
			continue ;
		}
		str = ft_strtrim(next);
		ret = process_opcode(op_tab + i, str, err);
		free(str);
		return (ret);
	}
	*err = get_error(UNVALID_NO_OPCODE);
	return (FALSE);
}

int			check_op(char *str, t_error **err, t_list **token_op)
{
	char		*space;
	size_t		size;
	int			ret;

	size = ft_strlen(str);
	if (!size)
		return (TRUE);
	space = ft_strchr(str, ' ');
	if (!space)
		return (process_label(str, err, token_op, size));
	if (!process_label(str, err, token_op, space - str))
		return (FALSE);
	str = ft_strtrim(space);
	ret = process_op(str, err, token_op);
	free(str);
	return (ret);
}
