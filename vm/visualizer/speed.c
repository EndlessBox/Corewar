/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:15:42 by ybouladh          #+#    #+#             */
/*   Updated: 2019/12/27 23:03:05 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			init_speed_bars(int *vis_speed)
{
	int	jumper;

	jumper = 0;
	attron(COLOR_PAIR(12) | A_BOLD);
	mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5, 65 * SCALE_H +
	((jumper / SPEED) * SCALE_H) + LEFT_BORDER, "%-8s :", "Speed");
	attroff(COLOR_PAIR(12) | A_BOLD);
	attron(COLOR_PAIR(13));
	while (jumper <= (*vis_speed))
	{
		mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5, 80 * SCALE_H +
		((jumper / SPEED) * SCALE_H) + LEFT_BORDER, "  ");
		jumper += SPEED;
	}
}

void			max_min_speed(int *vis_speed)
{
	int x;
	int jumper;

	x = *vis_speed == 0 ? 14 : 9;
	jumper = 0;
	attron(COLOR_PAIR(x) | A_BOLD);
	while (jumper < MAX_SPEED)
	{
		mvprintw((SEPARATOR_TOP + BORDER_TOP + 0) * SCALE_J + 5,
		(80 * SCALE_H) + ((jumper / SPEED) * SCALE_H) + LEFT_BORDER, "XX");
		jumper += SPEED;
	}
	attroff(COLOR_PAIR(x) | A_BOLD);
}

void			up_down_volume(int *vis_speed, int in)
{
	int	jumper;

	jumper = 0;
	refresh();
	attron(COLOR_PAIR(13));
	if (in == '-' && (*vis_speed) < MAX_SPEED)
		decrease_speed(vis_speed);
	else if (in == '+' && (*vis_speed) > 0)
		increase_speed(vis_speed);
	else if (in == -1)
		init_speed_bars(vis_speed);
	if ((*vis_speed) == MAX_SPEED || (*vis_speed) == 0)
		max_min_speed(vis_speed);
	refresh();
	attroff(COLOR_PAIR(13));
}
