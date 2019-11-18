/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:33:14 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/13 02:56:46 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    *last_player(t_player *players)
{
    t_player    *temp;

    temp = players;
    while (temp->next)
        temp = temp->next;
    return (temp);
}

t_monitor   *init_monitor(t_player *players)
{
    t_monitor   *monitor;

    if (!(monitor = (t_monitor*)malloc(sizeof(t_monitor))))
        ft_error("MONITOR ALLOCATION ERROR");
    monitor->last_pl_alive = last_player(players);
    monitor->cycle_counter = 0;
    monitor->cycle_to_die = -1;
    monitor->prev_ctd_lives = 0;
    monitor->check_performed = 0;
    return (monitor);
}

void        check_still_alive(t_queue *queue, int curr_cycle)
{
    t_addr      *temp;
    t_process   *current;

    if (!queue->first)
        return ;
    temp = queue->first;
    while (temp)
    {
        current = temp->addr;
        if (CYCLE_TO_DIE - current->last_live_performed < 0)
            ft_pop(queue, temp);
        temp = temp->next;

    }
}