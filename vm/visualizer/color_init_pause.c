/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_init_pause.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:43:24 by ybouladh          #+#    #+#             */
/*   Updated: 2020/01/04 00:15:18 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

WINDOW	*init_vis(void)
{
	WINDOW *scr;

	scr = initscr();
	start_color();
	cbreak();
	noecho();
	nodelay(scr, TRUE);
	curs_set(0);
	init_color(COLOR_GREEN, 176, 176, 176);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(1, COLOR_CYAN, COLOR_CYAN);
	init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(3, COLOR_BLUE, COLOR_BLUE);
	init_pair(4, COLOR_BLUE, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_CYAN);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_WHITE, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_BLACK);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_pair(13, COLOR_WHITE, COLOR_WHITE);
	init_pair(14, COLOR_WHITE, COLOR_MAGENTA);
	return (scr);
}

void	apply_update_pause(t_vm *vm, WINDOW *scr, int in)
{
	vm->visu_event = vm->visu_event == 'x' && in == 'p' ? 'p' : 'x';
	vis_state(vm->visu_event);
	if (in == 'p')
	{
		nodelay(scr, FALSE);
		while (vm->visu_spd != 'p' &&
		((in = getch()) == ERR || !(in == 'r' || in == 'n')))
			;
		if (in == 'r')
		{
			nodelay(scr, TRUE);
			vm->visu_event = 'x';
			vis_state(vm->visu_event);
		}
		if (in == 'n' && vm->visu_event == 'p')
			return ;
	}
}

void	put_color_players(t_vm *vm, int **size, int jumper, int *xopper)
{
	*xopper = size[0][jumper] - 1;
	attron(COLOR_PAIR(jumper + 1 + 4) | A_BOLD);
	while (++(*xopper) < size[1][jumper])
		mvprintw(((*xopper) / 128) * SCALE_J + BORDER_TOP,
		((*xopper) % 128) * SCALE_H + ((COLS - 128 * SCALE_H) / 2),
		"%02x", vm->arena.memory[(*xopper)]);
	attroff(COLOR_PAIR(jumper + 1 + 4) | A_BOLD);
	attron(COLOR_PAIR(10));
	while (jumper + 1 < vm->nb_players && ++(*xopper) < size[1][jumper + 1])
		mvaddstr(((*xopper) / 128) * SCALE_J + BORDER_TOP, ((*xopper) % 128)
		* SCALE_H + ((COLS - 128 * SCALE_H) / 2), "00");
	attroff(COLOR_PAIR(10));
}

void	init_players_vs(t_vm *vm, int **size)
{
	int jumper;
	int xopper;

	jumper = -1;
	xopper = -1;
	while (++jumper < vm->nb_players)
		put_color_players(vm, size, jumper, &xopper);
	attron(COLOR_PAIR(10));
	while (xopper < MEM_SIZE)
	{
		mvaddstr((xopper / 128) * SCALE_J + BORDER_TOP, (xopper % 128) *
		SCALE_H + ((COLS - 128 * SCALE_H) / 2), "  ");
		xopper++;
	}
	attroff(COLOR_PAIR(10));
	getch();
}
