/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_until_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:19:58 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/24 01:29:57 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_skip_unitl_char(const char *str, const char *compare)
{
	while (str && *str && !ft_isinstr(*str, compare))
		str++;
	return (str);
}

char		*ft_rskip_unitl_char(const char *str, const char *compare, int i)
{
	while (i >= 0 && ((!str[i]) || !ft_isinstr(str[i], compare)))
		i--;
	if (i == -1)
		i = 0;
	return ((char *)(str + i));
}
