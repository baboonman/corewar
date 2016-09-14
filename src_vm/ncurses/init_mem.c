/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mem.h"

void			init_mem(t_ncurses *ncurses)
{
	int			i;
	int			j;

	i = 0;
	while (i < MEM_HEIGHT)
	{
		j = 0;
		while (j < MEM_WIDTH - 2)
		{
			if ((j % 3) == 0)
				mvwprintw(ncurses->window[WIN_MEM], i, j, " ");
			else
				mvwprintw(ncurses->window[WIN_MEM], i, j, "0");
			j++;
		}
		i++;
	}
}
