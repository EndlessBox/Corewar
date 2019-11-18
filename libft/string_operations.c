/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:26:02 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/02/10 16:50:10 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_pow_of_5(char *holder, size_t h_len, size_t power)
{
	int		rest;
	int		i;

	ft_memset(holder, 0, h_len);
	holder[--h_len] = 1;
	while (power--)
	{
		i = h_len;
		rest = 0;
		while (i >= 0)
		{
			rest += holder[i] * 5;
			holder[i] = rest % 10;
			rest /= 10;
			i--;
		}
	}
	return (holder);
}

void		ft_sum(char *s1, int l1, char *s2, int l2)
{
	int		sum;

	sum = 0;
	while (l2 > 0)
	{
		sum += s1[--l1] + s2[--l2];
		s1[l1] = sum % 10;
		sum /= 10;
	}
	while (sum)
	{
		sum += s1[--l1];
		s1[l1] = sum % 10;
		sum /= 10;
	}
}

void		ft_div_by_2(char *s, int len, int repeat)
{
	int		d;
	int		i;

	while (*s == 0 && len--)
		s++;
	while (repeat >= 3)
	{
		i = 0;
		while (i < len - 1)
		{
			d = ((1 << 3) - 1) & s[i];
			s[i++] >>= 3;
			s[i] += d * 10;
		}
		repeat -= 3;
	}
	i = 0;
	d = 0;
	if (repeat)
		while (i < len - 1)
		{
			d = ((1 << repeat) - 1) & s[i];
			s[i++] >>= repeat;
			s[i] += d * 10;
		}
}

void		ft_mult_by_2(char *s, int len, int repeat)
{
	int		mult;
	int		i;

	while (repeat >= 26)
	{
		i = len - 1;
		mult = 0;
		while (i >= 0)
		{
			mult += s[i] << 26;
			s[i--] = mult % 10;
			mult /= 10;
		}
		repeat -= 26;
	}
	i = len - 1;
	mult = 0;
	while (i >= 0)
	{
		mult += s[i] << repeat;
		s[i--] = mult % 10;
		mult /= 10;
	}
}

void		ft_round(char *f, int len, int pr)
{
	int		i;

	if (pr + 1 < len)
	{
		if (f[pr + 1] > 5)
			f[pr]++;
		else if (f[pr + 1] == 5 && f[pr] & 1)
			f[pr]++;
		else if (f[pr + 1] == 5)
		{
			i = pr + 1;
			while (++i < len)
				if (f[i] != 0)
					break ;
			if (i < len)
				f[pr]++;
		}
		while (f[pr] >= 10)
		{
			f[pr - 1] += f[pr] / 10;
			f[pr--] %= 10;
		}
	}
}
