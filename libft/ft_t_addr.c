/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_addr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:22:52 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/24 02:04:25 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	malloc new node of type t_addr
*/

t_addr		*ft_new_t_addr(void *data)
{
	t_addr	*new;

	if (!(new = (t_addr*)malloc(sizeof(t_addr))))
		ft_error("can\'t malloc for new t_addr*");
	new->addr = data;
	new->next = NULL;
	return (new);
}

/*
**	add new t_addr node to last of linked list
*/

t_addr		*ft_push_t_addr(t_addr *head, void *addr)
{
	t_addr	*cur;

	cur = head;
	if (!head)
		return (ft_new_t_addr(addr));
	while (cur->next)
		cur = cur->next;
	cur->next = ft_new_t_addr(addr);
	return (head);
}

/*
**	remove node from linked list
*/

t_addr		*ft_remove_t_addr(t_addr *head, t_addr *node)
{
	t_addr	*cur;

	cur = head;
	if (head == node)
	{
		head = head->next;
		free(node);
		node = NULL;
	}
	else
	{
		while (cur->next && cur->next != node)
			cur = cur->next;
		if (cur->next)
		{
			cur->next = node->next;
			free(node);
			node = NULL;
		}
	}
	return (head);
}

/*
**	free linked list of t_addr
*/

void		ft_free_t_addr(t_addr *head)
{
	t_addr	*cur;

	while (head)
	{
		cur = head;
		head = head->next;
		free(cur);
	}
	head = NULL;
}
