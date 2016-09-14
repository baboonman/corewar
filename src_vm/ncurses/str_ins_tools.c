#include "str_ins_tools.h"

static char	*cat_param_str(char **str, int nb_param)
{
	size_t	tot_size;
	int		i;
	char	*final_str;

	tot_size = nb_param - 1;
	i = 0;
	while (i < nb_param)
	{
		tot_size += ft_strlen(str[i]);
		i++;
	}
	final_str = ft_strnew(tot_size);
	i = 0;
	while (i < nb_param)
	{
		ft_strcat(final_str, str[i]);
		free(str[i]);
		i++;
		if (i < nb_param)
			ft_strcat(final_str, " ");
	}
	return (final_str);
}

static char	*get_param_str(t_process *proc)
{
	int		nb_param;
	int		i;
	t_ins	*ins;
	char	*(str[3]);

	nb_param = g_op_tab[proc->curr_ins.opcode].nb_param;
	i = 0;
	ins = &(proc->curr_ins);
	while (i < nb_param)
	{
		if (ins->param_type[i] & T_REG)
			str[i] = get_reg_str(proc, ins->param_val[i]);
		else if (ins->param_type[i] & T_IND || ins->param_type[i] & T_DIR)
			str[i] = ft_itoa(ins->param_val[i]);
		i++;
	}
	return (cat_param_str(str, nb_param));
}

t_disp_ins	*get_str_invalid(t_process *proc)
{
	t_disp_ins	*disp_ins;
	char		*id_str;
	char		*msg_str;
	char		*res;

	msg_str = "Invalid instruction";
	id_str = get_proc_player_str(proc);
	res = ft_strnew(ft_strlen(id_str) + ft_strlen(msg_str));
	ft_strcat(res, id_str);
	ft_strcat(res, msg_str);
	free(id_str);
	disp_ins = safe_malloc(sizeof(t_disp_ins));
	disp_ins->str = res;
	disp_ins->player_id = proc->player_nb;
	return (disp_ins);
}

t_disp_ins	*get_str_ins(t_process *proc)
{
	char		*params;
	char		*name;
	char		*id;
	char		*res;
	t_disp_ins	*disp_ins;

	params = get_param_str(proc);
	name = g_op_tab[proc->curr_ins.opcode].name_op;
	id = get_proc_player_str(proc);
	disp_ins = safe_malloc(sizeof(t_disp_ins));
	res = ft_strnew(ft_strlen(params) + ft_strlen(name) + 16 + ft_strlen(id));
	ft_strcat(res, id);
	ft_strcat(res, name);
	ft_strcat(res, " ");
	ft_strcat(res, params);
	disp_ins->str = res;
	disp_ins->player_id = proc->player_nb;
	free(id);
	free(params);
	return (disp_ins);
}
