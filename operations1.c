/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 03:19:03 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/13 04:50:54 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void        check_operations(t_queue *queue)
{
    t_addr          *temp;
    extern t_op     op_tab[17];
    t_process       *current;
    unsigned int    op_code;

    temp = queue->first;
    while (temp)
    {
        current = temp->addr;
        if (current->cycle_before_exec == -1)
        {
            op_code = ((unsigned int*)(current->current_op))[0];
            if (op_code >= 1 && op_code <= 16)
            {
                current->cycle_before_exec = op_tab[op_code - 1].op_cycle_to_execute;
            }
        }
    }
}

void       op_live(t_monitor *game_monitor, t_process *process, t_player *player)
{
    game_monitor->prev_ctd_lives++;
    game_monitor->last_pl_alive = player;
    process->last_live_performed = game_monitor->cycle_counter;
}
