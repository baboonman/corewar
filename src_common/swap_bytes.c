/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:24 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:27 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap_bytes.h"

int16_t			swap_int16(int16_t v)
{
	return ((v << 8) | ((v >> 8) & 0xFF));
}

int32_t			swap_int32(int32_t v)
{
	v = ((v << 8) & 0xFF00FF00) | ((v >> 8) & 0xFF00FF);
	return (v << 16) | ((v >> 16) & 0xFFFF);
}

uint16_t		swap_uint16(uint16_t v)
{
	return ((v << 8) | (v >> 8));
}

uint32_t		swap_uint32(uint32_t v)
{
	v = ((v << 8) & 0xFF00FF00) | ((v >> 8) & 0xFF00FF);
	return ((v << 16) | (v >> 16));
}

int				swap_nbytes(int v, int nb_bytes)
{
	if (nb_bytes == 2)
		return (swap_uint16(v));
	if (nb_bytes == 4)
		return (swap_uint32(v));
	return (v);
}
