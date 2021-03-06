/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:23:21 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 22:36:36 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(const char *s, char *cmp)
{
	int	size;

	size = 0;
	if (s)
	{
		s = ft_skip_chars(s, cmp);
		while (*s)
		{
			size++;
			s = ft_skip_unitl_char(s, cmp);
			s = ft_skip_chars(s, cmp);
		}
	}
	return (size);
}
