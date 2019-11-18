/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:58:40 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/11 23:57:09 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process   *make_process(void)
{
	t_process   *process;
	static int  id;
	t_regs      regs;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		ft_error("PROCESS ALLOCATION ERROR");
	id++;
	process->id = id;
	process->carry = FALSE;
	process->current_op = NULL;
	process->last_live_performed = 0;
	process->cycle_before_exec = 0;
	process->bytes_to_next_op = 0;
	process->registers = malloc(REG_NUMBER * REG_SIZE);
	process->next = NULL;
	return (process);
}

t_queue     *make_affect_process(void *arena, t_player   *players, int players_nbr)
{
	t_queue     *queue;
	t_player    *temp;
	t_process   *process;
	int         jumper;

	temp = last_player(players);
	queue = ft_new_queue();
	jumper = 0;
	while (temp)
	{
		jumper = (MEM_SIZE / players_nbr) * (temp->id - 1);
		process = make_process();
		process->current_op = ((unsigned int*)arena) + jumper;
		((unsigned int*)process->registers)[r1] = temp->id;
		ft_enque(queue, process);
		temp = temp->previous;
	}
	return (queue);
}
