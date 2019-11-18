/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:03:07 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/13 04:19:32 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void        *initialize_map(t_player *players, int number)
{
    void        *arena;
    t_player    *temp;
    int         player_part;
    int         jumper;
    int         hopper;
    int         bubbler;

    if (!(arena = malloc(MEM_SIZE)))
        ft_error("ARENA ALLOCATION ERROR");
    temp = players;
    player_part = MEM_SIZE / number;
    jumper = 0;
    while (temp && jumper < MEM_SIZE)
    {
        bubbler = 0;
        hopper = jumper;
        while (bubbler < temp->exec_size)
            ((unsigned int*)arena)[hopper++] = temp->exec_code[bubbler++];
        while (hopper < CHAMP_MAX_SIZE)
            ((unsigned int *)arena)[hopper++] = 0x0;
        temp = temp->next;
        jumper += player_part;
    }
    return (arena);
}