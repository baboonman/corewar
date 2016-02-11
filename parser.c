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

void				write_header(char **bin, t_header *h)
{
	size_t			i;
	char			pad[4];

	ft_bzero(pad, 4);
	i = 0;
	i = ft_memcat(*bin, &(h->magic), i, sizeof(h->magic));
	i = ft_memcat(*bin, h->prog_name + 1, i, PROG_NAME_LENGTH);
	i = ft_memcat(*bin, pad, i, sizeof(pad));
	i = ft_memcat(*bin, &(h->prog_size), i, sizeof(h->prog_size));
	i = ft_memcat(*bin, h->comment + 1, i, COMMENT_LENGTH);
	ft_printf("%d bytes load to bin\n", i);
}

static int			process_section(t_bin_data *data, t_list* list_sections)
{
	t_token_section	*section;

write(1, "1\n", 2);
	(data->header)->magic = swap_uint32(COREWAR_EXEC_MAGIC);
//	header->prog_size = swap_uint32(7);
write(1, "2\n", 2);
	while (list_sections)
	{
write(1, "a\n", 2);
		section = list_sections->content;
		if (section->type == T_COMMENT)
			ft_strncpy(data->header->comment, section->value, COMMENT_LENGTH);
		else if (section->type == T_NAME)
			ft_strncpy(data->header->prog_name, section->value, PROG_NAME_LENGTH);
		list_sections = list_sections->next;
write(1, "b\n", 2);
	}
	if (ft_strlen(data->header->comment) == 0)
		return (FALSE);
	if (ft_strlen(data->header->prog_name) == 0)
		return (FALSE);
write(1, "3\n", 2);
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
			printf("%d << %d\n", code, (8 - (i + 1)*2));
		}
		else
		{
			ft_printf("token param nnot accepted\n");
		}
		i++;
	}
	return (ocp);
}

t_token_op			*fake_token()
{
	t_token_op		*token;
	
	token = malloc(sizeof(t_token_op));
	ft_bzero(token, sizeof(t_token_op));
	token->type = OP_TYPE_OP;
	token->op = 0x6;
	token->nb_param = 3;
	token->param_type[0] = T_IND;
	token->param_type[1] = T_DIR;
	token->param_type[2] = T_REG;
	token->param_val[0] = 34;		// 0x22
	token->param_val[1] = 23;		// 0x17
	token->param_val[2] = 1;		// 0x01
	return (token);
}

int					swap_nbytes(int v, int nbB)
{
	if (nbB == 2)
		return (swap_uint16(v));
	if (nbB == 4)
		return (swap_uint32(v));
	ft_printf("nb of bytes to swap not supported\n");
	return v;
}

int					process_token(t_bin_data *data, t_list* list_op)
{
	char			mask[3];
	t_token_op		*token;
	t_op			*op_info;
	char			ocp;
	char			line[128];
	size_t			size;
	int				i;
	int				j;
	int				param;

	i = 1;
	j = 0;
	ocp = 0;
	size = 0;
	token = fake_token();
	mask[0] = T_REG | T_DIR | T_IND; 	
	mask[1] = T_REG | T_DIR | T_IND; 	
	mask[2] = T_REG | T_DIR | T_IND; 	

	op_info = &(op_tab[token->op - 1]);
	if (op_info->has_opc)
		ocp = get_ocp(token, mask);
	
	line[0] = token->op;
	if (ocp)
	{
		line[i] = ocp;
		i++;
	}
	while (j < token->nb_param)
	{
		if (token->param_type[j] & T_REG)
		{
			i = ft_memcat(line, &(token->param_val[j]), i, 1);
		}
		else if (token->param_type[j] & T_DIR)
		{
			param = swap_nbytes(token->param_val[j], DIR_SIZE);
			i = ft_memcat(line, &(param), i, DIR_SIZE);
		}
		else if (token->param_type[j] & T_IND)
		{
			//param = swap_nbytes(token->param_val[j], IND_SIZE);
			param = swap_nbytes(15 - 20, IND_SIZE);
			i = ft_memcat(line, &(param), i, IND_SIZE);
		}
		j++;
	}
	printf("OCPFdP: 0x%x\n", (uint8_t)ocp);
	int		k = 0;
	printf("token: ");
	while (k < i)
	{
		printf("%x ", line[k]);
		k++;
	}
	printf("\n");

	ft_memcat(*bin_file, line, sizeof(t_header), i);
	return (0);
}

int					process_token(t_bin_data *data, t_list* op_tokens)
{
	t_token_op		*token;

	while (op_tokens)
	{

	}

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
	data->offset = 0;
	data->size = 0;
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
	i = ft_memcat(content, data->header, 0, sizeof(t_header));
//	i = ft_memcat(content, data->bin_file, i, data->size);

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

	if ((fd = open("test.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (ret_error("Unable to open file"));
	write_bin(fd, data);
	if ((close(fd)) < 0)
		return (ret_error("Unable to close file"));
	return (TRUE);
}
