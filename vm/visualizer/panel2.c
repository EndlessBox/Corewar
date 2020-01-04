/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 14:04:13 by ybouladh          #+#    #+#             */
/*   Updated: 2020/01/04 00:06:36 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	detail_panel(t_vm *vm)
{
	int	jumper;
	int	attr;

	jumper = -1;
	attr = 1;
	while (++jumper < vm->nb_players)
	{
		attron(COLOR_PAIR(attr));
		mvaddstr((SEPARATOR_TOP + BORDER_TOP + jumper) * SCALE_J + 5,
				5 + LEFT_BORDER, "  ");
		attroff(COLOR_PAIR(attr));
		refresh();
		attron(COLOR_PAIR(12) | A_BOLD);
		mvprintw((SEPARATOR_TOP + BORDER_TOP + jumper) * SCALE_J + 5,
				10 + LEFT_BORDER, "%s", vm->player[jumper].header.prog_name);
		attroff(COLOR_PAIR(12) | A_BOLD);
		attr++;
	}
}

void	help_panel(void)
{
	attron(COLOR_PAIR(12) | A_BOLD);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5, 20,
	"Mode : %10s, %5c : %-10s", "Running", 'p', "pause");
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 1) * SCALE_J + 5, 20,
	"Mode : %10s, %5s : %-10s", "Paused", "p + r", "resume");
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 2) * SCALE_J + 5, 20,
	"Mode : %10s, %5c : %-10s", "Paused", 'n', "next cycle");
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 3) * SCALE_J + 5, 20,
	"Mode : %10s, %5s : %-10s", "Running", "+/-", "speed up/down");
	attroff(COLOR_PAIR(12) | A_BOLD);
}

void	update_state(int jumper, t_vm *vm)
{
	t_arena arena;

	arena = vm->arena;
	attron(COLOR_PAIR(jumper + 5) | A_BOLD);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + jumper) * SCALE_J + 5,
	20 * SCALE_H + 35 + LEFT_BORDER, "%5d LIVE / PERIODE", vm->lifes[jumper]);
	attroff(COLOR_PAIR(jumper + 5) | A_BOLD);
	attron(COLOR_PAIR(12) | A_BOLD);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5,
	50 * SCALE_H + LEFT_BORDER, "%-12s : %13d", "Cycles", arena.cycle);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 1) * SCALE_J + 5,
	50 * SCALE_H + LEFT_BORDER, "%-12s : %5d / %5d", "Check",
	arena.count_current_cycle,
	arena.cycle_to_die);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 2) * SCALE_J + 5,
	50 * SCALE_H + LEFT_BORDER, "%-12s : %13d", "Processes",
	arena.nbr_process_alive);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 3) * SCALE_J + 5,
	50 * SCALE_H + LEFT_BORDER, "%-12s : %13d", "Check Nbr", arena.nbr_check);
	attroff(COLOR_PAIR(12) | A_BOLD);
	attron(COLOR_PAIR(11));
}

int		**players_exe_borders(t_player *players, int players_nbr)
{
	int	jumper;
	int	**size;
	int	step;

	jumper = -1;
	size = (int **)malloc(sizeof(int *) * 2);
	size[0] = (int *)malloc(sizeof(int) * players_nbr);
	size[1] = (int *)malloc(sizeof(int) * players_nbr);
	step = MEM_SIZE / players_nbr;
	while (++jumper < players_nbr)
	{
		size[0][jumper] = step * jumper;
		size[1][jumper] = (step * jumper) + players[jumper].header.prog_size;
	}
	return (size);
}
