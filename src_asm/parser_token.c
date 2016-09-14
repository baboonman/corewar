/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char			get_ocp(t_token_op *token, t_arg_type *mask, t_error **err)
{
	int				i;
	char			ocp;
	char			code;

	i = 0;
	ocp = 0;
	while (i < token->nb_param)
	{
		if (token->param_type[i] & mask[i])
		{
			if (token->param_type[i] & T_REG)
				code = REG_CODE;
			else if (token->param_type[i] & T_DIR)
				code = DIR_CODE;
			else if (token->param_type[i] & T_IND)
				code = IND_CODE;
			ocp |= (code << (8 - (i + 1) * 2));
		}
		else
			return (set_error_ret(err, INVALID_PARAM, token->line));
		i++;
	}
	return (ocp);
}

static t_error		*encode_param(t_bin_data *data, t_token_op *token,
									void **tricks, int j)
{
	char			*line;
	int				*i;
	int				size;
	int				param;
	t_op			*op_info;

	size = 666;
	line = (char*)tricks[0];
	i = (int*)(tricks[1]);
	op_info = &(g_op_tab[token->op - 1]);
	if (token->param_type[j] & T_REG)
		size = 1;
	else if (token->param_type[j] & T_IND || op_info->has_idx)
		size = IND_SIZE;
	else if (token->param_type[j] & T_DIR)
		size = DIR_SIZE;
	if (!check_overflow(token->param_val[j], size, token->line, tricks + 2))
		return (tricks[2]);
	if (token->param_type[j] & T_LAB)
		param = add_label_param(data, *i, size, token->param_lab[j]);
	else
		param = token->param_val[j];
	param = swap_nbytes(param, size);
	*i = ft_memcat(line, &(param), *i, size);
	return (NULL);
}

static t_error		*iterate_param(t_bin_data *data, t_token_op *token,
									char *line, int *i)
{
	int				j;
	t_error			*err;
	void			*tricks[3];

	j = 0;
	while (j < token->nb_param)
	{
		tricks[0] = line;
		tricks[1] = i;
		if ((err = encode_param(data, token, tricks, j)))
			return (err);
		j++;
	}
	return (NULL);
}

static int			compute_token(t_bin_data *data, t_token_op *token,
									t_error **err)
{
	t_op			*op_info;
	char			ocp;
	char			line[128];
	int				i;

	i = 1;
	ocp = 0;
	op_info = &(g_op_tab[token->op - 1]);
	if (op_info->has_opc)
		ocp = get_ocp(token, op_info->param_type, err);
	else
		check_param_type(token, op_info->param_type, err);
	if (*err)
		return (FALSE);
	line[0] = token->op;
	if (ocp)
		line[i++] = ocp;
	if ((*err = iterate_param(data, token, line, &i)))
		return (FALSE);
	if (data->size + i > CHAMP_MAX_SIZE)
		return (set_error_ret(err, INVALID_SIZE, token->line));
	ft_memcat(data->bin_file, line, data->size, i);
	data->size += i;
	return (TRUE);
}

int					process_token(t_bin_data *data, t_list *op_tokens)
{
	t_error			*err;
	t_token_op		*token;

	err = NULL;
	while (op_tokens)
	{
		token = op_tokens->content;
		if (token->type == OP_TYPE_LABEL)
			add_label(data, token);
		else if (!compute_token(data, token, &err))
			break ;
		op_tokens = op_tokens->next;
	}
	if (err)
	{
		ft_printf("Logic  error: line: %d, err: %s\n",
					err->line, err->description);
		return (FALSE);
	}
	return (TRUE);
}
