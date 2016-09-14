/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ins_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:21 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_ins_info.h"

void	update_ins_info(t_vm *vm)
{
	int			i;
	int			pos;
	int			player_color;
	t_ins_param	p;

	p.win = vm->ncurses.window[WIN_INS];
	getmaxyx(p.win, p.max_y, p.max_x);
	i = 0;
	pos = vm->ncurses.pos - 1;
	while (i < vm->ncurses.size)
	{
		player_color = find_player_by_nb_player(vm,
				vm->ncurses.lst_ins[(pos) % NB_INS_DISPLAY]->player_id);
		wattron(vm->ncurses.window[WIN_INS], COLOR_PAIR(player_color));
		mvwprintw(p.win, i, 0, "% *c", p.max_x - 1, ' ');
		mvwprintw(p.win, i, 0, "%s",
				vm->ncurses.lst_ins[(pos) % NB_INS_DISPLAY]->str);
		wattroff(vm->ncurses.window[WIN_INS], COLOR_PAIR(player_color));
		pos--;
		if (pos < 0)
			pos = vm->ncurses.size - 1;
		++i;
	}
}
