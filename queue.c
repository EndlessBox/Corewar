/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:55:13 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/11/13 02:55:07 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_queue			*ft_new_queue(void)
{
	t_queue		*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void			ft_enque(t_queue *q, void *data)
{
	t_addr	*temp;

	if (q->first)
	{
		q->last->next = ft_new_t_addr(data);
		q->last = q->last->next;
	}
	else
	{
		q->first = ft_new_t_addr(data);
		q->last = q->first;
	}
}

void			ft_pop(t_queue *q, t_addr *to_pop)
{
	t_addr		*temp;
	t_addr		*holder;

	if (!q->first)
		return ;
	temp = q->first;
	while (temp->next)
	{
		if (temp->next == to_pop)
		{
			holder = temp->next;
			temp->next = temp->next->next;
			ft_free_t_addr(holder);
		}
		temp = temp->next;
	}
}

int				ft_free_queue(t_queue *q)
{
	if (!q)
		return (1);
	if (q->last)
		ft_free_t_addr(q->first);
	free(q);
	q = NULL;
	return (1);
}
