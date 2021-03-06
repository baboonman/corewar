/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 16:46:20 by jrenouf-          #+#    #+#             */
/*   Updated: 2016/09/14 16:46:32 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_ncurses.h"

static void	set_init_val(void)
{
	initscr();
	noecho();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	start_color();
}

static int	create_borders(t_ncurses *ncurses)
{
	int		i;

	ncurses->border[WIN_INS] = newwin(TMP_BORD_HEIGHT, TMP_BORD_WIDTH,
			PLAYERS_INFO_BORD_HEIGHT - 1, MEM_WIDTH + 1);
	if (!(ncurses->border[WIN_INS]))
		return (FALSE);
	ncurses->border[WIN_MEM] = newwin(MEM_BORD_HEIGHT, MEM_BORD_WIDTH,
			PLAYERS_INFO_BORD_HEIGHT - 1, 0);
	if (!(ncurses->border[WIN_MEM]))
		return (FALSE);
	ncurses->border[WIN_INFO] = newwin(PLAYERS_INFO_BORD_HEIGHT,
			PLAYERS_INFO_BORD_WIDTH, 0, 0);
	if (!(ncurses->border[WIN_INFO]))
		return (FALSE);
	i = 0;
	while (i < 3)
		box(ncurses->border[i++], ACS_VLINE, ACS_HLINE);
	return (TRUE);
}

static int	create_windows(t_ncurses *ncurses)
{
	ncurses->window[WIN_INS] = newwin(INS_HEIGHT, INS_WIDTH,
			PLAYERS_INFO_BORD_HEIGHT + GLOB_HEIGHT, MEM_BORD_WIDTH + 1);
	if (!(ncurses->window[WIN_INS]))
		return (FALSE);
	ncurses->window[WIN_MEM] = newwin(MEM_HEIGHT, MEM_WIDTH,
			PLAYERS_INFO_BORD_HEIGHT, 1);
	if (!(ncurses->window[WIN_MEM]))
		return (FALSE);
	ncurses->window[WIN_INFO] = newwin(PLAYERS_INFO_HEIGHT, PLAYERS_INFO_WIDTH,
			1, 1);
	if (!(ncurses->window[WIN_INFO]))
		return (FALSE);
	ncurses->window[WIN_GLOB_INF] = newwin(GLOB_HEIGHT, TMP_WIDTH,
			PLAYERS_INFO_BORD_HEIGHT, MEM_BORD_WIDTH + 1);
	if (!(ncurses->window[WIN_GLOB_INF]))
		return (FALSE);
	return (TRUE);
}

static int	set_panel(t_ncurses *ncurses)
{
	int		i;
	int		pan_nb;

	i = 0;
	pan_nb = 0;
	while (i < 3)
	{
		if (!(ncurses->panel[pan_nb] = new_panel(ncurses->border[i])))
			return (FALSE);
		pan_nb++;
		if (!(ncurses->panel[pan_nb] = new_panel(ncurses->window[i])))
			return (FALSE);
		++i;
		pan_nb++;
	}
	if (!(ncurses->panel[pan_nb] = new_panel(ncurses->window[WIN_GLOB_INF])))
		return (FALSE);
	update_panels();
	doupdate();
	return (TRUE);
}

int			init_ncurses(t_ncurses *ncurses, t_vm *vm)
{
	set_init_val();
	set_color();
	create_borders(ncurses);
	create_windows(ncurses);
	set_panel(ncurses);
	init_mem(ncurses);
	refresh_mem_display(vm);
	return (TRUE);
}
