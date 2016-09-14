/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_live.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:19 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_LIVE_H
# define CHECK_LIVE_H

# include "corewar_struct.h"
# include "corewar_define.h"
# include "process_struct.h"
# include "op.h"
# include <ft_printf.h>

int		check_live(t_vm *vm);
void	kill_player(t_vm *vm, t_player *player);

#endif
