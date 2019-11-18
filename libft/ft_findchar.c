/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 14:18:02 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/23 22:37:53 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_findchar(char *str, char c)
{
	int	pos;

	pos = 0;
	if (!str)
		return (-2);
	while (str[pos])
		if (str[pos++] == c)
			return (pos - 1);
	if (str[pos] == c)
		return (pos);
	return (-1);
}
