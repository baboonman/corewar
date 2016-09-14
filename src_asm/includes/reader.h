/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <libft.h>
# include <ft_printf.h>

# include "safe_malloc.h"
# include "struct.h"
# include "utils.h"

# define SIZE_BUFF_LINE	4

t_file				*read_file(char *name);

#endif
