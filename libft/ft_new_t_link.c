/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_t_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:10 by ybouladh          #+#    #+#             */
/*   Updated: 2019/10/24 02:23:49 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_link		*ft_new_t_link(void *addr)
{
	t_link	*new;

	if (!(new = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	new->cost = 1;
	new->link = addr;
	new->next = NULL;
	return (new);
}
