/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:24 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:27 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "safe_malloc.h"

void		*safe_malloc(size_t size)
{
	void	*res;

	if (!(res = malloc(size)))
	{
		ft_printf("%rMalloc fail\n");
		exit(1);
	}
	return (res);
}
