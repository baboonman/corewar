/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			*err = get_error(INVALID_CHAR_LABEL);
			return (NULL);
		}
		i++;
	}
	op = safe_malloc(sizeof(t_token_op));
	ft_bzero(op, sizeof(t_token_op));
	op->type = OP_TYPE_LABEL;
	op->label = safe_malloc(size + 1);
	ft_strncpy(op->label, str, size);
	op->label[size] = '\0';
	return (op);
}

static int	process_label(char *str, t_error **err, t_list **token_op,
		size_t size)
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
	return (FALSE);
}

static int	process_label_op(char *str, t_error **err, t_list **token_op,
		size_t label_offset)
{
	int			ret;
	char		*space;

	space = ft_strchr_space(str);
	ret = process_label(str, err, token_op, label_offset);
	if (ret)
		str = space;
	str = ft_strtrim(str);
	ret = process_op(str, err, token_op);
	free(str);
	return (ret);
}

int			check_op(char *str, t_error **err, t_list **token_op)
{
	char		*space;
	size_t		size;

	size = ft_strlen(str);
	if (!size)
		return (TRUE);
	space = ft_strchr_space(str);
	if (!space)
		return (process_label(str, err, token_op, size));
	if (!process_label_op(str, err, token_op, space - str))
		return (FALSE);
	return (TRUE);
}
