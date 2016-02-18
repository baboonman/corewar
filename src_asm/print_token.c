#include "print_token.h"

void					*print_token(void *data)
{
	t_token_section		*section;

	section = data;
	ft_printf("type: %d, val: |%s|, line: %d\n", section->type, section->value,
			section->line);
	return (data);
}

void					*print_op(void *data)
{
	t_token_op		*op;
	int				i;

	op = data;
	if (op->type == OP_TYPE_LABEL)
		ft_printf("type: label, label: %s, line: %d\n", op->label, op->line);
	else
	{
		i = 0;
		ft_printf("Type: %d, op: %d, line: %d", op->type, op->op, op->line);
		while (i < op->nb_param)
		{
			if (op->param_type[i] & T_LAB)
				ft_printf(", p%d: type: %d(label), val: %s", i,
						op->param_type[i] & (~T_LAB), op->param_lab[i]);
			else
				ft_printf(", p%d: type: %d, val: %d", i, op->param_type[i],
						op->param_val[i]);
			i++;
		}
		ft_printf("\n");
	}
	return (data);
}
