#include "lexer_op.h"

t_token_op	*check_label(char *str, size_t size, t_error **err)
{
	size_t		i;

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
}

int			check_op(char *str, t_error **err, t_list **token_op)
{
	char		*space;
	size_t		size;
	t_token_op	*op;

	size = ft_strlen(str);
	if (!size)
		return (TRUE);
	space = ft_strchr(str, " ");
	if (!space)
	{
		if (str[size - 1] == LABEL_CHAR)
		{
			if ((op = check_label(str, size - 1, err)))
				ft_lstadd(token_op, ft_lstnew(op, sizeof(*op)));
			else
				return (FALSE);
		}
	}
}
