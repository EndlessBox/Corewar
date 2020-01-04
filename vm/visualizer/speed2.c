/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 13:59:25 by ybouladh          #+#    #+#             */
/*   Updated: 2019/12/27 23:03:09 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int				clear_volume(void)
{
	int	jumper;

	jumper = 0;
	attroff(COLOR_PAIR(13));
	attron(COLOR_PAIR(11));
	while (jumper < 100000)
	{
		mvprintw((SEPARATOR_TOP + BORDER_TOP) * SCALE_J + 5, (80 * SCALE_H) +
		((jumper / SPEED) * SCALE_H) + LEFT_BORDER, "  ");
		jumper += SPEED;
	}
	refresh();
	attroff(COLOR_PAIR(11));
	attron(COLOR_PAIR(13));
	return (1);
}

void			decrease_speed(int *vis_speed)
{
	int	jumper;

	jumper = 0;
	*vis_speed += SPEED;
	clear_volume();
	while (jumper < (MAX_SPEED - (*vis_speed)))
	{
		mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5,
		(80 * SCALE_H) + ((jumper / SPEED) * SCALE_H) + LEFT_BORDER, "  ");
		jumper += SPEED;
	}
}

void			increase_speed(int *vis_speed)
{
	int	jumper;

	jumper = 0;
	*vis_speed -= SPEED;
	clear_volume();
	while (jumper < (MAX_SPEED - (*vis_speed)))
	{
		mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5,
		(80 * SCALE_H) + ((jumper / SPEED) * SCALE_H) + LEFT_BORDER, "  ");
		refresh();
		jumper += SPEED;
	}
}

void			line(t_vm *vm)
{
	int	jumper;

	jumper = 9;
	vm->bytes[0][0].status = 0;
	attron(COLOR_PAIR(vm->winner));
	while (++jumper < COLS - 10)
		mvaddch((BORDER_TOP + 32) * SCALE_J, jumper, ' ');
	attroff(COLOR_PAIR(vm->winner));
	refresh();
}
