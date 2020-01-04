/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:24:03 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/12/27 14:23:40 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc2(void *tab, int oldlen, int newlen, size_t size)
{
	void	*newtab;

	if (!(newtab = malloc((newlen + 1) * size)))
		return (NULL);
	ft_memset(newtab, 0, (newlen + 1) * size);
	ft_memcpy(newtab, tab, oldlen * size);
	free(tab);
	return (newtab);
}
