/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_ncurses.h"

int		set_color(void)
{
	if (init_pair(1, COLOR_BLUE, COLOR_BLACK) == ERR)
		return (FALSE);
	if (init_pair(2, COLOR_RED, COLOR_BLACK) == ERR)
		return (FALSE);
	if (init_pair(3, COLOR_GREEN, COLOR_BLACK) == ERR)
		return (FALSE);
	if (init_pair(4, COLOR_YELLOW, COLOR_BLACK) == ERR)
		return (FALSE);
	if (init_pair(5, COLOR_BLACK, COLOR_WHITE) == ERR)
		return (FALSE);
	if (init_pair(6, COLOR_BLACK, COLOR_BLUE) == ERR)
		return (FALSE);
	if (init_pair(7, COLOR_BLACK, COLOR_RED) == ERR)
		return (FALSE);
	if (init_pair(8, COLOR_BLACK, COLOR_GREEN) == ERR)
		return (FALSE);
	if (init_pair(9, COLOR_BLACK, COLOR_YELLOW) == ERR)
		return (FALSE);
	return (TRUE);
}
