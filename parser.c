#include "parser.h"

size_t				ft_memcat(void *dest, void *src, size_t i, size_t n)
{
	size_t			j;
	unsigned char		*ua_dest;
	const unsigned char	*ua_src;

	j = 0;
	ua_dest = (unsigned char *)dest;
	ua_src = (const unsigned char *)src;
	while (j < n)
	{
		ua_dest[i] = ua_src[j];
		i++;
		j++;
	}
	return (i);
}

static int			process_section(t_bin_data *data, t_list* list_sections)
{
	t_token_section	*section;

	(data->header)->magic = swap_uint32(COREWAR_EXEC_MAGIC);
	while (list_sections)
	{
		section = list_sections->content;
		if (section->type == T_COMMENT)
			ft_strncpy(data->header->comment, section->value, COMMENT_LENGTH);
		else if (section->type == T_NAME)
			ft_strncpy(data->header->prog_name, section->value, PROG_NAME_LENGTH);
		list_sections = list_sections->next;
	}
	if (ft_strlen(data->header->comment) == 0)
		return (FALSE);
	if (ft_strlen(data->header->prog_name) == 0)
		return (FALSE);
	return (TRUE);
}

char				get_ocp(t_token_op *token, char *mask)
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
			ocp |= (code << (8 - (i + 1)*2));
		}
		else
		{
			ft_printf("token param nnot accepted\n");
		}
		i++;
	}
	return (ocp);
}

t_label_offset		*search_label(t_bin_data *data, char *name)
{
	size_t			i;

	i = 0;
	while (i < data->lo_size)
	{
		if (!ft_strcmp(data->lo[i]->name, name))
			return (data->lo[i]);
		i++;
	}
	return (NULL);
}

int					add_label_param(t_bin_data *data, int off, int size, char *label_name)
{
	t_label_param	*lab_param;
	t_label_offset	*lab_off;
	t_label_param	**ntab;
	size_t			j;

	if ((lab_off = search_label(data, label_name)))
		return (lab_off->offset - data->size);

	lab_param = (t_label_param*)malloc(sizeof(t_label_param));
	if (!lab_param)
		ret_error("malloc failed");
	lab_param->name = ft_strdup(label_name);
	lab_param->offset = off;
	lab_param->size = size;
	lab_param->PC = data->size;

	ntab = malloc(sizeof(t_label_offset*) * (data->pl_size + 1));
	if (!ntab)
		ret_error("malloc failed");
	j = 0;
	while (j < data->pl_size)
	{
		ntab[j] = (data->pl)[j];
		j++;
	}
	ntab[j] = lab_param;
	free(data->pl);
	data->pl = ntab;
	data->pl_size++;
	return (0);
}

int					compute_token(t_bin_data *data, t_token_op *token, t_error **err)
{
	t_op			*op_info;
	char			ocp;
	char			line[128];
	int				i;
	int				j;
	int				param;
	int				size;

	i = 1;
	j = 0;
	ocp = 0;
	size = 0;
	op_info = &(op_tab[token->op - 1]);
	if (op_info->has_opc)
		ocp = get_ocp(token, op_info->param_type);
	
	line[0] = token->op;
	if (ocp)
	{
		line[i] = ocp;
		i++;
	}
	while (j < token->nb_param)
	{
		if (token->param_type[j] & T_LAB)
		{
			if (token->param_type[j] & T_IND || op_info->has_idx)
				size = IND_SIZE;
			else
				size = DIR_SIZE;
			param = add_label_param(data, i, size, token->param_lab[j]);
			param = swap_nbytes(param, size);
			i = ft_memcat(line, &(param), i, size);
		}
		else if (token->param_type[j] & T_REG)
		{
			i = ft_memcat(line, &(token->param_val[j]), i, 1);
		}
		else if (token->param_type[j] & T_IND || op_info->has_idx)
		{
			param = swap_nbytes(token->param_val[j], IND_SIZE);
			i = ft_memcat(line, &(param), i, IND_SIZE);
		}
		else if (token->param_type[j] & T_DIR)
		{
			param = swap_nbytes(token->param_val[j], DIR_SIZE);
			i = ft_memcat(line, &(param), i, DIR_SIZE);
		}
		j++;
	}
	ft_memcat(data->bin_file, line, data->size, i);
	data->size += i;
	return (TRUE);
}

int					add_label(t_bin_data *data, t_token_op *token)
{
	t_label_offset	**ntab;
	size_t			j;
	t_label_offset	*lab_off;

	lab_off = (t_label_offset*)malloc(sizeof(t_label_offset));
	if (!lab_off)
		return (ret_error("malloc failed"));
	lab_off->name = ft_strdup(token->label);
	lab_off->offset = data->size;

	ntab = malloc(sizeof(t_label_offset*) * (data->lo_size + 1));
	if (!ntab)
		ret_error("malloc failed");
	j = 0;
	while (j < data->lo_size)
	{
		ntab[j] = (data->lo)[j];
		j++;
	}
	ntab[j] = lab_off;
	free(data->lo);
	data->lo = ntab;
	data->lo_size++;
	return (TRUE);
}

int					process_token(t_bin_data *data, t_list* op_tokens)
{
	t_error			*err;
	t_token_op		*token;

	err  = NULL;
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
		ft_printf("Logic  error: line: %d, err: %s\n", err->line, err->description);
		return (FALSE);
	}
	return (TRUE);
}

t_bin_data			*init_bin_data(int *ret)
{
	t_bin_data *data;

	data = (t_bin_data*)malloc(sizeof(t_bin_data));
	if (!data)
		*ret = ret_error("malloc failed");
	data->bin_file = (char*)malloc(sizeof(char) * CHAMP_MAX_SIZE);
	if (!(data->bin_file))
		*ret = ret_error("malloc failed");
	data->header = (t_header*)malloc(sizeof(t_header));
	if (!(data->header))
		*ret = ret_error("malloc failed");
	ft_bzero(data->header, sizeof(t_header));
	data->size = 0;
	data->pl = malloc(sizeof(t_label_param*));
	data->pl_size = 0;
	data->lo = malloc(sizeof(t_label_offset*));
	data->lo_size = 0;
	*ret = TRUE;
	return (data);
}

void				free_bin_data(t_bin_data *data)
{
	free(data->header);
	free(data->bin_file);
	free(data);
	data = NULL;
}

int					write_bin(int fd, t_bin_data *data)
{
	int				wr_ret;
	size_t			i;
	char			*content;

	content = (char*)malloc(sizeof(char) * CHAMP_MAX_SIZE + sizeof(t_header));
	if (!content)
		return (ret_error("malloc failed"));
	data->header->prog_size = swap_uint32(data->size);
	i = ft_memcat(content, data->header, 0, sizeof(t_header));
	i = ft_memcat(content, data->bin_file, i, data->size);
	if ((wr_ret = write(fd, content, i)) < 0)
		return (ret_error("Unable to write to file"));
	else 
		ft_printf("%d bytes written to files\n", wr_ret);
	return (wr_ret);
}

int					process_file(t_file* file)
{
	int				fd;
	int				ret;
	t_bin_data		*data;

	data = init_bin_data(&ret);
	if (!ret)
		return (FALSE);

	process_section(data, file->list_sections);
	process_token(data, file->list_op);
//	process_label(data);

	if ((fd = open("test.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (ret_error("Unable to open file"));
	write_bin(fd, data);
	if ((close(fd)) < 0)
		return (ret_error("Unable to close file"));
	return (TRUE);
}
