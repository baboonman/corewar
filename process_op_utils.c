#include "process_op_utils.h"

char		*remove_space(char *str)
{
	int			size;

	while (*str != '\0' && *str == ' ')
		str++;
	size = ft_strlen(str) - 1;
	while (size >= 0 && str[size] == ' ')
		str[size--] = '\0';
	return (str);
}

int			get_reg(char *str)
{
	char	*tmp;
	int		reg_nb;

	if (*str != 'r')
		return (-1);
	str++;
	if (*str == '\0')
		return (-1);
	tmp = str;
	while (*str != '\0' && ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (-1);
	reg_nb = ft_atoi(tmp);
	if (reg_nb > 0 && reg_nb <= REG_NUMBER)
		return (reg_nb);
	return (-1);
}

int			get_label(char *str, char **label)
{
	char	*tmp;

	tmp = str;
	if (*str == '\0')
		return (FALSE);
	while (*str != '\0')
	{
		if (!ft_strchr(LABEL_CHARS, *str))
			return (FALSE);
		str++;
	}
	*label = ft_strdup(tmp);
	return (TRUE);
}

int			get_dir(char *str, int *match, char **label)
{
	int		dir_val;
	char	*tmp;

	if (*str != '%')
	{
		*match = FALSE;
		return (0);
	}
	str++;
	if (*str == LABEL_CHAR)
	{
		*match = get_label(str + 1, label);
		return (0);
	}
	tmp = str;
	if (*str == '-')
		str++;
	if (*str == '\0')
	{
		*match = FALSE;
		return (0);
	}
	while (*str != '\0' && ft_isdigit(*str))
		str++;
	if (*str != '\0')
	{
		*match = FALSE;
		return (0);
	}
	dir_val = ft_atoi(tmp);
	return (dir_val);
}

int			get_ind(char *str, int *match, char **label)
{
	char		*tmp;

	if (*str == LABEL_CHAR)
	{
		*match = get_label(str + 1, label);
		return (0);
	}
	tmp = str;
	if (*str == '-')
		str++;
	if (*str == '\0')
	{
		match = FALSE;
		return (0);
	}
	while (*str != '\0' && ft_isdigit(*str))
		str++;
	if (*str != '\0')
	{
		*match = FALSE;
		return (0);
	}
	return (ft_atoi(tmp));
}
