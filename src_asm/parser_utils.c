/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int64_t				ft_pow(int64_t x, int n)
{
	int64_t			y;

	y = 1;
	while (n)
	{
		y *= x;
		n--;
	}
	return (y);
}

int					check_overflow(int64_t v, int nb_bytes, int cur_line,
									void **error)
{
	int64_t			lim;
	t_error			*err;

	lim = ft_pow(256, nb_bytes) / 2;
	if (v >= lim - 1 || v < -1 * lim)
	{
		err = get_error(OVERFLOW);
		err->line = cur_line;
		*error = err;
		return (FALSE);
	}
	return (TRUE);
}

size_t				ft_memcat(void *dest, void *src, size_t i, size_t n)
{
	ft_memcpy(dest + i, src, n);
	i += n;
	return (i);
}
