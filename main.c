/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:58:29 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/13 22:35:09 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int     main(int argc, char **argv)
{
	extern t_op			op_tab[17];
	t_player			*players;
	t_monitor			*game_monitor;
	t_queue				*queue;
	int					players_number;
	unsigned int		*arena;
	t_process			*proc;
	t_addr				*temp;
	int					temp_cycle_to_die;
	// t_hello				hey;

	players_number = 0;
	players = get_players(argv, argc, &players_number);
	arena = initialize_map(players, players_number);
	DB_show_arena(arena);
	game_monitor = init_monitor(players);
	queue = make_affect_process(arena, players, players_number);
	players_introduction(players);
	// ft_printf("%s\n", op)
	// temp_cycle_to_die = game_monitor->cycle_to_die;
	// while (temp_cycle_to_die)
	// {
	// 	temp_cycle_to_die--;
	// 	game_monitor->cycle_counter++;
	// 	if (temp_cycle_to_die == 0)
	// 	{
	// 		/*
	// 		 * Check number of lifes performed during 
	// 		 * the last cycle to die and apply change to it 
	// 		 *  or re-initialize it !
	// 		 * and update check performed if the live declared
	// 		 * before are less then NBR_LIVE
	// 		 */
	// 		if (game_monitor->prev_ctd_lives >= NBR_LIVE)
	// 		{
	// 			game_monitor->check_performed = 1;
	// 			game_monitor->cycle_to_die -= CYCLE_DELTA;
	// 			check_still_alive(queue, game_monitor->cycle_counter);
	// 		}
	// 		else
	// 		{
	// 			game_monitor->check_performed++;
	// 			if (game_monitor->check_performed == MAX_CHECKS)
	// 			{
	// 				/*
	// 				 * Check if MAX_CHECKS is reached and cycle to 
	// 				 * die is decremented with  CYCLE_DELTA , if
	// 				 *  i have to re-initialize the check_performed.
	// 				 */
	// 				game_monitor->cycle_to_die -= CYCLE_DELTA;
	// 			}
	// 		}
	// 		temp_cycle_to_die = game_monitor->cycle_to_die;
	// 		/*
	// 		 * Check also if i checked ? should i execute the operation
	// 		 * that are ready to be executed ?  or move to the next cycle
	// 		 * to do that ?
	// 		 */
	// 	}
	// 	else if (temp_cycle_to_die > 0)
	// 	{
	// 		temp = queue->first;
	// 		while (temp)
	// 		{
	// 			proc = temp->addr;
	// 			/*
	// 			 * Check if the operation every process stand on is 
	// 			 *  ready to be executed (that mean if the 
	// 			 *  process->cycle_before_exec == 0)
	// 			 *  if c_b_e is equal to zero (after decrementation)
	// 			 *  then check the operation code if exist then exec it
	// 			 *  and point on the new operation.
	// 			 *  if the operation code we are standing on is false
	// 			 *  move to the next byte ! and do nothing !
	// 			 */
	// 			check_op(queue);
	// 			temp = temp->next;
	// 		}
	// 	}
		
	// }
	return (0);
}
