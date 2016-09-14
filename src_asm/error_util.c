/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:48:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_util.h"

t_error		*get_error(char *description)
{
	t_error		*err;

	err = safe_malloc(sizeof(t_error));
	ft_bzero(err, sizeof(t_error));
	ft_strncpy(err->description, description, MAX_SIZE_ERROR);
	return (err);
}

void		*print_error(void *data)
{
	t_error	*err;

	err = data;
	ft_printf("Syntax error: line: %d, err: %s\n", err->line, err->description);
	return (data);
}

int			ret_error(char *description)
{
	ft_printf("Error: %s\n", description);
	return (FALSE);
}

int			set_error_ret(t_error **err, char *desc, int line)
{
	*err = get_error(desc);
	(*err)->line = line;
	return (FALSE);
}
