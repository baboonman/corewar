/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ARG_H
# define PARSE_ARG_H

# include "corewar_struct.h"
# include "corewar_define.h"
# include "parse_player_arg.h"

# include <libft.h>
# include <ft_printf.h>

int			parse_ncurses(char **av, t_param *param);
int			parse_verbose(char **av, t_param *param);
int			parse_arg(t_param *param, int ac, char **av);

#endif
