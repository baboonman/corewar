/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:24 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:27 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_BYTES_H
# define SWAP_BYTES_H

# include <stdint.h>

int16_t			swap_int16(int16_t v);
int32_t			swap_int32(int32_t v);
uint16_t		swap_uint16(uint16_t v);
uint32_t		swap_uint32(uint32_t v);
int				swap_nbytes(int v, int nb_bytes);

#endif
