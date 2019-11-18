/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_t_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:50:32 by ybouladh          #+#    #+#             */
/*   Updated: 2019/08/05 14:25:33 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str		*ft_new_t_str(char *s, int len)
{
	t_str	*new;

	if (!(new = (t_str*)malloc(sizeof(t_str))))
		return (NULL);
	if (len != 0)
		new->str = ft_strndup(s, len);
	else
		new->str = ft_strdup(s);
	new->next = NULL;
	new->visited = 0;
	return (new);
}
