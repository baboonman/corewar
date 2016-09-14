/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_section.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:48:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:49:04 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_SECTION_H
# define CHECK_SECTION_H

# include "struct.h"
# include "op.h"
# include "error_util.h"
# include "lexer_op.h"

# define T_COMMENT		1
# define T_NAME			2

# define SIZE_NAME_CMD	(sizeof(NAME_CMD_STRING) - 1)
# define SIZE_COMMENT_CMD (sizeof(COMMENT_CMD_STRING) - 1)

t_token_section				*check_section(char *str, t_error **error,
		size_t *line, t_file *file);
char						*get_str(size_t *line, t_file *file, char *start);

#endif
