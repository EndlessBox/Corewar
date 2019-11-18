/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:25:58 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/11 13:04:51 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    DB_show_players(t_player *player, int norm_rev)
{
	int jumper;
	int hopper;
	t_player    *temp;

	if (norm_rev == 1)
		temp = last_player(player);
	temp = norm_rev == 1 ? last_player(player) : player;
	while (player)
	{
		ft_printf("Player id : %d\nPlayer name : %s\nPlayer comment : %s\nPlayer size : %d\n",
				player->id, (char*)player->name, player->comment, player->exec_size);
		jumper = 0;
		while (jumper < player->exec_size)
		{
			ft_printf("%x", player->exec_code[jumper]);
			jumper++;  
		}
		ft_printf("\n\n\n");
		if (norm_rev == 1)
			player = player->previous;
		else
			player = player->next;
	}
}

void    DB_show_arena(void *arena)
{
	int     jumper;

	jumper = 0;
	while (jumper < MEM_SIZE)
	{
		ft_printf("%2x", ((int*)arena)[jumper]);
		if (jumper % 64 == 0 && jumper != 0)
			ft_putchar('\n');
		jumper++;
	}
}

void    DB_show_monitor(t_monitor *monitor)
{
	ft_printf("Last player alive : %s\n", ((t_player*)monitor->last_pl_alive)->name);
	ft_printf("Cylces sum : %d\n", monitor->cycle_counter);
	ft_printf("Cycle to die : %d\n", monitor->cycle_to_die);
	ft_printf("Live perforned last cycle to die : %d\n", monitor->prev_ctd_lives);
	ft_printf("Checks performed : %d\n", monitor->check_performed);
	ft_putendl("\n");
}
