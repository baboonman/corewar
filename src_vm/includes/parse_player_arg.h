/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_arg.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_PLAYER_ARG_H
# define PARSE_PLAYER_ARG_H

# include "corewar_struct.h"
# include "corewar_define.h"
# include "check_ext.h"

# include <ft_printf.h>
# include <libft.h>

int				parse_player_arg(t_param *param, char **av, int ac);

#endif
