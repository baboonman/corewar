/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_STRUCT_H
# define PROCESS_STRUCT_H

# include "op.h"

typedef struct				s_ins
{
	int						opcode;
	size_t					size;
	int						param_val[3];
	t_arg_type				param_type[3];
}							t_ins;

typedef struct				s_process
{
	int						reg[REG_NUMBER];
	int						carry;
	int						number_cycles;
	int						pc;
	t_ins					curr_ins;
	int						player_nb;
	int						nb_live;
	int						proc_nb;
}							t_process;

#endif
