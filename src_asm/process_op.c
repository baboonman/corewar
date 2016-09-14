/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:01 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_op.h"

static int			get_param(t_op *opcode, char *str, char *param[3],
		t_error **err)
{
	int		p_idx;
	int		idx;

	p_idx = 0;
	param[p_idx] = str--;
	while (*(++str) != '\0')
	{
		if (*str == SEPARATOR_CHAR)
		{
			*(str++) = '\0';
			if (++p_idx >= 3)
			{
				*err = get_error(INVALID_TOO_MANY_PARAM);
				return (-1);
			}
			param[p_idx] = str;
		}
	}
	if ((idx = p_idx + 1) == opcode->nb_param)
		return (idx);
	if (idx < opcode->nb_param)
		*err = get_error(INVALID_NOT_ENOUGH_PARAM);
	else
		*err = get_error(INVALID_TOO_MANY_PARAM);
	return (-1);
}

static char			set_param(int64_t tmp_val, int64_t *val,
		char **lab_val, char type_p)
{
	char	type;

	type = type_p;
	if (*lab_val)
		type |= T_LAB;
	else
		*val = tmp_val;
	return (type);
}

static int			get_type_val(char *type, int64_t *val, char **lab_val,
		char *param)
{
	int64_t		tmp_val;
	int			ret;

	tmp_val = get_reg(param);
	if (tmp_val > 0)
	{
		*type = T_REG;
		*val = tmp_val;
		return (TRUE);
	}
	ret = TRUE;
	*lab_val = NULL;
	tmp_val = get_dir(param, &ret, lab_val);
	if (ret)
		return ((*type = set_param(tmp_val, val, lab_val, T_DIR)) || TRUE);
	ret = TRUE;
	*lab_val = NULL;
	tmp_val = get_ind(param, &ret, lab_val);
	if (ret)
		return ((*type = set_param(tmp_val, val, lab_val, T_IND)) || TRUE);
	return (FALSE);
}

static t_token_op	*process_opcode(t_op *opcode, char *str_param,
		t_error **err)
{
	t_token_op		*op;
	char			*param[3];
	int				i;
	int				nb_param;

	if ((nb_param = get_param(opcode, str_param, param, err)) < 0)
		return (NULL);
	op = safe_malloc(sizeof(t_token_op));
	ft_bzero(op, sizeof(t_token_op));
	i = 0;
	while (i < nb_param)
	{
		if (!get_type_val(op->param_type + i, op->param_val + i,
					op->param_lab + i, remove_space(param[i])))
		{
			*err = get_error(INVALID_PARAM);
			free(op);
			return (NULL);
		}
		i++;
	}
	op->nb_param = nb_param;
	op->type = OP_TYPE_OP;
	return (op);
}

int					process_op(char *str, t_error **err, t_list **token_op)
{
	char		*next;
	int			i;
	size_t		size;
	t_token_op	*op;

	next = ft_strchr_space(str);
	if (next == NULL)
		return ((*err = get_error(INVALID_NO_PARAM)) && FALSE);
	size = next - str;
	i = 0;
	while (g_op_tab[i].name_op)
	{
		if ((ft_strlen(g_op_tab[i].name_op) != size
				|| ft_strncmp(g_op_tab[i].name_op, str, size) != 0) && ++i)
			continue ;
		str = ft_strtrim(next);
		op = process_opcode(g_op_tab + i, str, err);
		free(str);
		if (!op)
			return (FALSE);
		op->op = g_op_tab[i].op_code;
		ft_lstadd(token_op, ft_lstnew(op, sizeof(t_token_op)));
		return (TRUE);
	}
	return ((*err = get_error(INVALID_NO_OPCODE)) && FALSE);
}
