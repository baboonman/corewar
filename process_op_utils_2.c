#include "process_op_utils.h"

static int	set_match_return_zero(int *match, int match_val)
{
	*match = match_val;
	return (0);
}

int64_t		get_dir(char *str, int *match, char **label)
{
	int		dir_val;
	char	*tmp;

	if (*str != '%')
		return (set_match_return_zero(match, FALSE));
	str++;
	if (*str == LABEL_CHAR)
		return (set_match_return_zero(match, get_label(str + 1, label)));
	tmp = str;
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (set_match_return_zero(match, FALSE));
	while (*str != '\0' && ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (set_match_return_zero(match, FALSE));
	if (ft_strlen(tmp) >= 12)
		return (set_match_return_zero(match, FALSE));
	dir_val = ft_atoli(tmp);
	return (dir_val);
}

int64_t		get_ind(char *str, int *match, char **label)
{
	char		*tmp;

	if (*str == LABEL_CHAR)
		return (set_match_return_zero(match, get_label(str + 1, label)));
	tmp = str;
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (set_match_return_zero(match, FALSE));
	while (*str != '\0' && ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (set_match_return_zero(match, FALSE));
	if (ft_strlen(tmp) >= 12)
		return (set_match_return_zero(match, FALSE));
	return (ft_atoli(tmp));
}
