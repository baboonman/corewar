/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:49:00 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "lexer_op.h"
# include "check_section.h"
# include "print_token.h"

# include <ft_printf.h>
# include <libft.h>
# include <list.h>

# define ERROR_LEXICAL 1
# define NO_ERROR 0

int		parse_file(t_file *file);

#endif
