/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 00:23:31 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/14 05:57:01 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_chars(const char *str, const char *compare)
{
	while (str && *str && ft_isinstr(*str, compare))
		str++;
	return ((char *)str);
}

char	*ft_rskip_chars(const char *str, const char *compare, int i)
{
	while (i >= 0 && (!str[i] || ft_isinstr(str[i], compare)))
		i--;
	if (i == -1)
		i = 0;
	return ((char *)(str + i));
}
