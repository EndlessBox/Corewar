/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_t_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:47:02 by ybouladh          #+#    #+#             */
/*   Updated: 2019/10/23 01:48:18 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_link		*ft_push_t_link(t_link *head, void *addr)
{
	t_link	*curr;

	curr = head;
	if (!head)
		return (ft_new_t_link(addr));
	else
	{
		while (curr->next)
		{
			if (curr->link == addr)
				return (head);
			curr = curr->next;
		}
		if (curr->link != addr)
			if (!(curr->next = ft_new_t_link(addr)))
				return (NULL);
	}
	return (head);
}
