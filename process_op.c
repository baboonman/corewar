#include "process_op.h"

static int			get_param(t_op *opcode, char *str, char *param[3], t_error **err, int *idx)
{
	int		p_idx;

	p_idx = 0;
	param[p_idx] = str--;
	while (*(++str) != '\0')
	{
		if (*str == SEPARATOR_CHAR)
		{
			*(str++) = '\0';
			if (++p_idx >= 3)
			{
				*err = get_error(UNVALID_TOO_MANY_PARAM);
				return (FALSE);
			}
			param[p_idx] = str;
		}
	}
	*idx = p_idx + 1;
	if (*idx == opcode->nb_param)
		return (TRUE);
	if (*idx < opcode->nb_param)
		*err = get_error(UNVALID_NOT_ENOUGH_PARAM);
	else
		*err = get_error(UNVALID_TOO_MANY_PARAM);
	return (FALSE);
}

static int			set_param(int tmp_val, char *type, int *val,
		char **lab_val, char type_p)
{
	*type = type_p;
	if (*lab_val)
		*type |= T_LAB;
	else
		*val = tmp_val;
	return (TRUE);
}

static int			get_type_val(char *type, int *val, char **lab_val,
		char *param)
{
	int		tmp_val;
	int		ret;

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
		return (set_param(tmp_val, type, val, lab_val, T_DIR));
	ret = TRUE;
	*lab_val = NULL;
	tmp_val = get_ind(param, &ret, lab_val);
	if (ret)
		return (set_param(tmp_val, type, val, lab_val, T_IND));
	return (FALSE);
}

static t_token_op	*process_opcode(t_op *opcode, char *str_param, t_error **err)
{
	t_token_op		*op;
	char			*param[3];
	int				i;
	int				nb_param;

	if (!get_param(opcode, str_param, param, err, &nb_param))
		return (NULL);
	op = malloc(sizeof(t_token_op));
	ft_bzero(op, sizeof(t_token_op));
	i = 0;
	while (i < nb_param)
	{
		if (!get_type_val(op->param_type + i, op->param_val + i,
					op->param_lab + i, remove_space(param[i])))
		{
			*err = get_error(UNVALID_PARAM);
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
	{
		*err = get_error(UNVALID_NO_PARAM);
		return (FALSE);
	}
	size = next - str;
	i = 0;
	while (op_tab[i].name_op)
	{
		if (ft_strlen(op_tab[i].name_op) != size
				|| ft_strncmp(op_tab[i].name_op, str, size) != 0)
		{
			i++;
			continue ;
		}
		str = ft_strtrim(next);
		op = process_opcode(op_tab + i, str, err);
		free(str);
		if (op)
		{
			op->op = op_tab[i].op_code;
			ft_lstadd(token_op, ft_lstnew(op, sizeof(t_token_op)));
			return (TRUE);
		}
		return (FALSE);
	}
	*err = get_error(UNVALID_NO_OPCODE);
	return (FALSE);
}
