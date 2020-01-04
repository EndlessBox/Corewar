/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:42:00 by ybouladh          #+#    #+#             */
/*   Updated: 2020/01/04 00:06:08 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	update_life_bars(t_vm *vm, int jumper)
{
	int hopper;
	int	xopper;

	hopper = 0;
	xopper = 0;
	attron(COLOR_PAIR(jumper + 1));
	while (hopper < vm->lifes[jumper] &&
	hopper < 20 * 4)
	{
		mvaddstr((SEPARATOR_TOP + BORDER_TOP + jumper) * SCALE_J + 5,
		xopper * SCALE_H + 35 + LEFT_BORDER, "  ");
		hopper += 4;
		xopper++;
	}
	attroff(COLOR_PAIR(jumper + 1));
}

void	init_update_panel(t_vm *vm)
{
	int			jumper;
	int			xopper;
	t_player	*players;

	jumper = -1;
	players = vm->player;
	while (++jumper < vm->nb_players)
	{
		xopper = -1;
		refresh();
		if (vm->arena.count_current_cycle % vm->arena.cycle_to_die == 0)
		{
			while (++xopper < vm->nb_players)
				vm->lifes[xopper] = 0;
			xopper = -1;
			attron(COLOR_PAIR(11));
			while (++xopper < 20)
				mvaddstr((SEPARATOR_TOP + BORDER_TOP + jumper) * SCALE_J + 5,
				xopper * SCALE_H + 35 + LEFT_BORDER, "  ");
			attroff(COLOR_PAIR(11));
		}
		update_life_bars(vm, jumper);
		update_state(jumper, vm);
	}
	attroff(COLOR_PAIR(11));
}

void	vis_state(char vis_state)
{
	char	*str;

	attron(COLOR_PAIR(12) | A_BOLD);
	str = vis_state == 'p' ? "PAUSED " : "RUNNING";
	mvprintw(2, (COLS - 7) / 2, "%s", str);
	attroff(COLOR_PAIR(12) | A_BOLD);
	refresh();
}
