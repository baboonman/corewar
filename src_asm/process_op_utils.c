/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_op_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:01 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_op_utils.h"

char		*remove_space(char *str)
{
	int			size;

	while (*str != '\0' && (*str == ' ' || *str == '\t'))
		str++;
	size = ft_strlen(str) - 1;
	while (size >= 0 && (str[size] == ' ' || *str == '\t'))
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
