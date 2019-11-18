/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:26:02 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/02/10 18:16:17 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_precise(char *f, int size, t_prefix pr)
{
	int		i;
	int		j;
	int		h;
	char	*res;

	pr.p = (pr.p == -1) ? 6 : pr.p;
	ft_round(f, size, pr.p + (h = size / 2) - 1);
	i = 0;
	while (f[i] == 0 && i < h)
		i++;
	j = 0;
	res = (char*)malloc((pr.p + 2 + (h - i == 0 ? 1 : h - i)) * sizeof(char));
	if (h - i == 0)
		res[j++] = '0';
	else
		while (i < h)
			res[j++] = f[i++] + '0';
	res[j++] = (!ft_strchr(pr.f, '#') && pr.p <= 0) ? '\0' : '.';
	while (pr.p-- && i < size)
		res[j++] = f[i++] + '0';
	while (pr.p-- >= 0)
		res[j++] = '0';
	res[j] = '\0';
	free(f);
	return (res);
}

char		*ft_double(char *bits, t_prefix pr)
{
	char	*res;
	char	*p;
	char	power[37];
	int		i;

	if (!ft_strncmp("11111111111", bits + 1, 11))
		return (ft_strdup(ft_strchr(bits + 12, '1') ? "nan" : "inf"));
	if (!ft_strncmp("00000000000", bits + 1, 11) && !ft_strchr(bits + 12, '1'))
		return (ft_precise(ft_strnew(2), 2, pr));
	res = ft_strnew(D_MX_SIZE);
	res[D_MX_SIZE / 2 - 1] = ft_strnchr(bits + 1, '1', 11) ? 1 : 0;
	p = bits + 12;
	i = 0;
	while (p[i])
		if (p[i++] == '1')
			ft_sum(res, D_MX_SIZE / 2 + i, ft_pow_of_5(power, 37, i), 37);
	p = ft_strndup(bits + 1, 11);
	i = base_to_dec(p, 2) - D_BIAS;
	if (i < 0)
		ft_div_by_2(res, D_MX_SIZE, -i);
	else
		ft_mult_by_2(res, D_MX_SIZE, i);
	free(p);
	return (ft_precise(res, D_MX_SIZE, pr));
}

char		*ft_long_double(char *bits, t_prefix pr)
{
	char	*res;
	char	*p;
	char	power[46];
	int		i;

	if (!ft_strncmp("1111111111111111", bits + 1, 16))
		return (ft_strdup(ft_strchr(bits + 17, '1') ? "nan" : "inf"));
	if (!ft_strncmp("0000000000000000", bits + 1, 16) &&
			!ft_strchr(bits + 12, '1'))
		return (ft_precise(ft_strnew(2), 2, pr));
	res = ft_strnew(LD_MX_SIZE);
	res[LD_MX_SIZE / 2 - 1] = (bits[16] == '1') ? 1 : 0;
	p = bits + 17;
	i = 0;
	while (p[i])
		if (p[i++] == '1')
			ft_sum(res, LD_MX_SIZE / 2 + i, ft_pow_of_5(power, 46, i), 46);
	p = ft_strndup(bits + 1, 15);
	i = base_to_dec(p, 2) - LD_BIAS;
	if (i < 0)
		ft_div_by_2(res, LD_MX_SIZE, -i);
	else
		ft_mult_by_2(res, LD_MX_SIZE, i);
	free(p);
	return (ft_precise(res, LD_MX_SIZE, pr));
}

int			ft_print_double(double f, t_prefix *pr)
{
	char	*res;
	char	*bits;
	char	s;
	int		c;

	bits = ft_read_memory((char*)&f, sizeof(f));
	res = ft_double(bits, *pr);
	s = (bits[0] == '1') ? '-' : '\0';
	if (s != '-' && (ft_strchr(pr->f, '+') || ft_strchr(pr->f, ' ')))
		s = (ft_strchr(pr->f, '+')) ? '+' : ' ';
	c = ft_strlen(res) + ((s) ? 1 : 0);
	if (pr->w > c && !ft_strchr(pr->f, '-') && (!ft_strchr(pr->f, '0') ||
				res[0] == 'i' || res[0] == 'n'))
		c += ft_put_ntime(' ', pr->w - c);
	if (s)
		ft_putchar(s);
	if (pr->w > c && ft_strchr(pr->f, '0') && !ft_strchr(pr->f, '-'))
		c += ft_put_ntime('0', pr->w - c);
	ft_putstr(res);
	if (pr->w > c && ft_strchr(pr->f, '-') && !ft_strchr(pr->f, '0'))
		c += ft_put_ntime(' ', pr->w - c);
	free(bits);
	free(res);
	return (c);
}

int			ft_print_long_double(long double f, t_prefix *pr)
{
	char	*res;
	char	*bits;
	char	s;
	int		c;

	bits = ft_read_memory((char*)&f, 10);
	res = ft_long_double(bits, *pr);
	s = (bits[0] == '1') ? '-' : '\0';
	if (s != '-' && (ft_strchr(pr->f, '+') || ft_strchr(pr->f, ' ')))
		s = (ft_strchr(pr->f, '+')) ? '+' : ' ';
	c = ft_strlen(res) + ((s) ? 1 : 0);
	if (pr->w > c && !ft_strchr(pr->f, '-') && (!ft_strchr(pr->f, '0') ||
				res[0] == 'i' || res[0] == 'n'))
		c += ft_put_ntime(' ', pr->w - c);
	if (s)
		ft_putchar(s);
	if (pr->w > c && ft_strchr(pr->f, '0') && !ft_strchr(pr->f, '-'))
		c += ft_put_ntime('0', pr->w - c);
	ft_putstr(res);
	if (pr->w > c && ft_strchr(pr->f, '-') && !ft_strchr(pr->f, '0'))
		c += ft_put_ntime(' ', pr->w - c);
	free(bits);
	free(res);
	return (c);
}
