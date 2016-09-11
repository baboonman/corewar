#include "launch_vm.h"
#include <sys/time.h>

static int	init_player_process(t_vm *vm, t_player *player, size_t pos)
{
	t_process	*process;
	t_list		*list;

	process = safe_malloc(sizeof(t_process));
	ft_bzero(process, sizeof(t_process));
	process->reg[0] = player->nb;
	process->pc = pos;
	process->number_cycles = 0;
	process->player_nb = player->nb;
	process->proc_nb = vm->nb_proc++;
	list = ft_lstnew(process, sizeof(t_process));
	list->next = vm->lst_process;
	vm->lst_process = list;
	return (TRUE);
}

static int	write_player(t_vm *vm)
{
	int			i;
	int			offset;
	t_player	*player;
	size_t		off;

	i = 0;
	offset = MEM_SIZE / vm->nb_players;
	while (i < vm->nb_players)
	{
		player = vm->players + i;
		off = i * offset;
		ft_memcpy(vm->mem_space + off, player->bin, player->size_bin - sizeof(t_header));
		init_player_process(vm, player, off);
		++i;
	}
	return (TRUE);
}

static int	init_vm_function(t_vm *vm)
{
	vm->ins_function[0] = ins_live;
	vm->ins_function[1] = ins_ld;
	vm->ins_function[2] = ins_st;
	vm->ins_function[3] = ins_add;
	vm->ins_function[4] = ins_sub;
	vm->ins_function[5] = ins_and;
	vm->ins_function[6] = ins_or;
	vm->ins_function[7] = ins_xor;
	vm->ins_function[8] = ins_zjump;
	vm->ins_function[9] = ins_ldi;
	vm->ins_function[10] = ins_sti;
	vm->ins_function[11] = ins_fork;
	vm->ins_function[12] = ins_lld;
	vm->ins_function[13] = ins_lldi;
	vm->ins_function[14] = ins_lfork;
	vm->ins_function[15] = ins_aff;
	return (TRUE);
}

static int	init_vm(t_vm *vm)
{
	vm->nb_proc = 1;
	vm->mem_space = safe_malloc(MEM_SIZE);
	ft_bzero(vm->mem_space, MEM_SIZE);
	write_player(vm);
	init_vm_function(vm);
	vm->cycle_die.to_die = CYCLE_TO_DIE;
	vm->cycle_die.step = CYCLE_TO_DIE;
	if (vm->param.is_ncurses)
		return (init_ncurses(&(vm->ncurses), vm));
	return (1);
}

int			sub_time(struct timeval a, struct timeval b, int tps)
{
	unsigned long int	t1, t2, t3;
	

	t1 = a.tv_sec * 1000000 + a.tv_usec;
	t2 = b.tv_sec * 1000000 + b.tv_usec;
	t3 = (unsigned long int)( (1.0f / tps) * 1000000.0f);

	if (t2 - t1 > t3)
		return (1);
	return (0);
}

void		print_progress(t_vm *vm, int j)
{
	int		i;

	i = j % 8;
	if (i == 0)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "|");
	else if (i == 1)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "/");
	else if (i == 2)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "-");
	else if (i == 3)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "\\");
	else if (i == 4)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "|");
	else if (i == 5)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "/");
	else if (i == 6)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "-");
	else if (i == 7)
		mvwprintw(vm->ncurses.window[WIN_INFO], 1, 0, "\\");

}

int			launch_vm(t_vm *vm)
{
	int		i;
	int		flag;
	int		exec_ret;
	int		tps = 301;
	struct timeval		a, b;
	int		c;

	exec_ret = 1;
	flag = 0;
	i = 0;
	if (!init_vm(vm))
		return (FALSE);
	gettimeofday(&a, NULL);
	while (1)
	{
//		c = wgetch(stdscr);
		c = getch();
		if (c == 67)
		{
			if (tps < 1000)
				tps += 50;
		}
		else if (c == 68)
		{
			if (tps > 50)
				tps -= 50;
		}
		else if (c == 65)
			tps = 1001;
		else if (c == 66)
			tps = 1;
//		else if ( c > 0 )
//		{
//			mvwprintw(vm->ncurses.window[WIN_INFO], 0, 15, "  %d    ", c);
//		}
		gettimeofday(&b, NULL);
		if (sub_time(a, b, tps))
		{
			exec_ret = execute_loop(vm);
			gettimeofday(&a, NULL);
			mvwprintw(vm->ncurses.window[WIN_INFO], 0, 0, "%d    %f   ", tps, 1.0f / tps);
			print_progress(vm, i);
			++i;
		}
		if (!exec_ret)
		{
			if (vm->param.verbose)
				ft_printf("Total number of loop: %d\n", i);
			break ;
		}
//		print_progress(vm, i);
//		++i;
		if (vm->param.is_dump && vm->param.nb_cycle_dump <= i)
		{
			flag = 1;
			dump_memory(vm);
			break ;
		}
		update_panels();
		doupdate();
	}
	if (vm->param.is_ncurses)
		quit_ncurses(&(vm->ncurses));
	if (!flag & vm->param.is_dump)
	{
		ft_printf("Ending before end of dump\n");
		dump_memory(vm);
	}
	return (TRUE);
}
