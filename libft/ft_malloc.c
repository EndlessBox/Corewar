/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:12:18 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/12/27 11:51:43 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (new)
		ft_bzero(new, size);
	else
		ft_error("Can't malloc");
	return (new);
}
