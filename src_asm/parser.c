#include "parser.h"

static int			process_section(t_bin_data *data, t_list *list_sections)
{
	t_token_section	*sect;

	(data->header)->magic = swap_uint32(COREWAR_EXEC_MAGIC);
	while (list_sections)
	{
		sect = list_sections->content;
		if (sect->type == T_COMMENT)
			ft_strncpy(data->header->comment, sect->value, COMMENT_LENGTH);
		else if (sect->type == T_NAME)
			ft_strncpy(data->header->prog_name, sect->value, PROG_NAME_LENGTH);
		list_sections = list_sections->next;
	}
	return (TRUE);
}

static t_bin_data	*init_bin_data(int *ret)
{
	t_bin_data		*data;

	data = (t_bin_data*)safe_malloc(sizeof(t_bin_data));
	data->bin_file = (char*)safe_malloc(sizeof(char) * CHAMP_MAX_SIZE);
	data->header = (t_header*)safe_malloc(sizeof(t_header));
	ft_bzero(data->header, sizeof(t_header));
	data->size = 0;
	data->pl = safe_malloc(sizeof(t_label_param*));
	data->pl_size = 0;
	data->lo = safe_malloc(sizeof(t_label_offset*));
	data->lo_size = 0;
	*ret = TRUE;
	return (data);
}

static void			free_bin_data(t_bin_data *data)
{
	size_t			i;

	i = 0;
	free(data->header);
	free(data->bin_file);
	while (i < data->pl_size)
	{
		free((data->pl)[i]);
		i++;
	}
	i = 0;
	while (i < data->lo_size)
	{
		free((data->lo)[i]);
		i++;
	}
	free(data->pl);
	free(data->lo);
	free(data);
	data = NULL;
}

static int			write_bin(int fd, t_bin_data *data)
{
	int				wr_ret;
	size_t			i;
	char			*content;

	content = safe_malloc(sizeof(char) * CHAMP_MAX_SIZE + sizeof(t_header));
	if (!content)
		return (ret_error("safe_malloc failed"));
	data->header->prog_size = swap_uint32(data->size);
	i = ft_memcat(content, data->header, 0, sizeof(t_header));
	i = ft_memcat(content, data->bin_file, i, data->size);
	if ((wr_ret = write(fd, content, i)) < 0)
		return (ret_error("Unable to write to file"));
	else
		ft_printf("%d bytes written to files\n", wr_ret);
	free(content);
	return (wr_ret);
}

int					process_file(t_file *file)
{
	int				fd;
	int				ret;
	t_bin_data		*data;

	data = init_bin_data(&ret);
	if (!ret)
		return (FALSE);
	if (!process_section(data, file->list_sections) ||
		!process_token(data, file->list_op) ||
		!process_label(data))
		return (FALSE);
	if ((fd = open(file->cor_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (ret_error("Unable to open file"));
	write_bin(fd, data);
	if ((close(fd)) < 0)
		return (ret_error("Unable to close file"));
	free_bin_data(data);
	return (TRUE);
}
