/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_UTILS_H
# define MEM_UTILS_H

# include "swap_bytes.h"
# include "op.h"
# include <stddef.h>
# include <ft_printf.h>

int			read_n_bytes(int size, void *mem, size_t off);
void		write_n_bytes(int size, void *mem, size_t off, int val);

#endif
