#include "parser.h"

static t_label_offset	*search_label(t_bin_data *data, char *name)
{
	size_t				i;

	i = 0;
	while (i < data->lo_size)
	{
		if (!ft_strcmp(data->lo[i]->name, name))
			return (data->lo[i]);
		i++;
	}
	return (NULL);
}

int						add_label_param(t_bin_data *data, int off, int size,
									char *label_name)
{
	t_label_param		*lab_param;
	t_label_offset		*lab_off;
	t_label_param		**ntab;
	size_t				j;

	if ((lab_off = search_label(data, label_name)))
		return (lab_off->offset - data->size);
	lab_param = (t_label_param*)safe_malloc(sizeof(t_label_param));
	lab_param->name = ft_strdup(label_name);
	lab_param->offset = off;
	lab_param->size = size;
	lab_param->pc = data->size;
	ntab = safe_malloc(sizeof(t_label_offset*) * (data->pl_size + 1));
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

int						add_label(t_bin_data *data, t_token_op *token)
{
	t_label_offset		**ntab;
	size_t				j;
	t_label_offset		*lab_off;

	lab_off = (t_label_offset*)safe_malloc(sizeof(t_label_offset));
	lab_off->name = ft_strdup(token->label);
	lab_off->offset = data->size;
	ntab = safe_malloc(sizeof(t_label_offset*) * (data->lo_size + 1));
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

static void				inject_label(t_bin_data *data, t_label_param *lp,
									size_t label_off)
{
	int					param;

	param = swap_nbytes(label_off - lp->pc, lp->size);
	ft_memcpy(data->bin_file + lp->pc + lp->offset, &(param), lp->size);
}

int						process_label(t_bin_data *data)
{
	size_t				i;
	t_label_offset		*lab_off;

	i = 0;
	while (i < data->pl_size)
	{
		if ((lab_off = search_label(data, data->pl[i]->name)))
			inject_label(data, data->pl[i], lab_off->offset);
		else
		{
			ft_printf("Logic  error: %s: %s\n",
						"Invalid label", data->pl[i]->name);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
