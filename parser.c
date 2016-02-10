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

static int			process_section(char **bin_file, t_list* list_sections)
{
	t_header		*header;
	t_token_section	*section;

	header = (t_header*)malloc(sizeof(t_header));
	if (!header)
		return (ret_error("malloc failed"));
	ft_bzero(header, sizeof(t_header));
	header->magic = swap_uint32(COREWAR_EXEC_MAGIC);
//	header->prog_size = swap_uint32(7);
	while (list_sections)
	{
		section = list_sections->content;
		if (section->type == T_COMMENT)
			ft_strncpy(header->comment, section->value, COMMENT_LENGTH);
		else if (section->type == T_NAME)
			ft_strncpy(header->prog_name, section->value, PROG_NAME_LENGTH);
		list_sections = list_sections->next;
	}
	if (ft_strlen(header->comment) == 0)
		return (FALSE);
	if (ft_strlen(header->prog_name) == 0)
		return (FALSE);
	ft_memcpy(*bin_file, header, sizeof(t_header));
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
		i++;
	}
	return (ocp);
}

int					process_token(t_bin_data *data, t_list* list_op)
{
	char			mask[3];
	t_token_op		*token;
	char			ocp;

	token = malloc(sizeof(t_token_op));
	ft_bzero(token, sizeof(t_token_op));
	token->nb_param = 3;
	token->param_type[0] = T_REG;
	token->param_type[1] = T_IND;
	token->param_type[2] = T_DIR;
	mask[0] = T_REG | T_DIR | T_IND; 	
	mask[1] = T_REG | T_DIR | T_IND; 	
	mask[2] = T_REG | T_DIR | T_IND; 	
	ocp = get_ocp(token, mask);
	printf("OCPFdP: 0x%x\n", ocp);
	return (0);
}

int					process_file(t_file* file)
{
	int				fd;
	size_t			bin_size;
	char			*bin_file;
	int				wr_ret;

	bin_size = CHAMP_MAX_SIZE + sizeof(t_header) + 1;
	bin_file = (char*)malloc(bin_size);
	if (!bin_file)
		return (ret_error("malloc failed"));
	if ((fd = open("test.cor", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (ret_error("Unable to open file"));
	process_section(&bin_file, file->list_sections);
	process_token(NULL, NULL);
	if ((wr_ret = write(fd, bin_file, sizeof(t_header))) < 0)
		return (ret_error("Unable to write file"));
	else 
		ft_printf("%d bytes written to files\n", wr_ret);
	if ((close(fd)) < 0)
		return (ret_error("Unable to close file"));
	return (TRUE);
}
