/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 23:46:00 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/02/25 21:23:39 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_print_percente(t_prefix *pr)
{
	int		res;
	int		wlen;
	char	fill;

	res = 0;
	wlen = pr->w - 1;
	fill = (ft_strchr(pr->f, '0')) ? '0' : ' ';
	if (pr->p != 0)
		while (wlen-- > 0 && !ft_strchr(pr->f, '-') && ++res)
			ft_putchar(fill);
	res += ft_putchar('%');
	if (pr->p != 0)
		while (wlen-- + 1 > 0 && ft_strchr(pr->f, '-') && ++res)
			ft_putchar(' ');
	return (res);
}

int			ft_print_c(t_prefix *pr, int c)
{
	int		i;
	int		wlen;
	char	fill;

	fill = ' ';
	if (ft_strchr(pr->f, '0') && !ft_strchr(pr->f, '-'))
		fill = '0';
	i = -1;
	wlen = 1;
	if (ft_strchr(pr->f, '-'))
		ft_putchar(c);
	while (++i < pr->w - wlen)
		ft_putchar(fill);
	if (!ft_strchr(pr->f, '-'))
		ft_putchar(c);
	return (i + wlen);
}

int			ft_print_wc(t_prefix *pr, int c)
{
	int		i;
	int		wlen;
	int		s[2];
	char	fill;

	fill = ' ';
	if (ft_strchr(pr->f, '0') && !ft_strchr(pr->f, '-'))
		fill = '0';
	i = -1;
	s[0] = c;
	s[1] = 0;
	wlen = ft_strwlen(s);
	if (ft_strchr(pr->f, '-'))
		ft_putwchar(c);
	while (++i < pr->w - wlen)
		ft_putchar(fill);
	if (!ft_strchr(pr->f, '-'))
		ft_putwchar(c);
	return (i + wlen);
}

int			ft_print_s(t_prefix *pr, char *str)
{
	int		res;
	int		wlen;
	char	fill;
	char	*s;

	if (!str)
		str = "(null)";
	if (pr->p != -1)
		s = ft_strndup(str, pr->p);
	else
		s = ft_strdup(str);
	res = 0;
	wlen = pr->w - ft_strlen(s);
	fill = (ft_strchr(pr->f, '0')) ? '0' : ' ';
	while (wlen-- > 0 && !ft_strchr(pr->f, '-') && ++res)
		ft_putchar(fill);
	res += ft_lputstr(s);
	while (wlen-- + 1 > 0 && ft_strchr(pr->f, '-') && ++res)
		ft_putchar(' ');
	free(s);
	return (res);
}

int			ft_print_ws(t_prefix *pr, char *str)
{
	int		res;
	int		wlen;
	char	fill;
	char	*s;

	if (!str)
		str = "(null)";
	if (pr->p != -1)
		s = ft_strndup(str, pr->p);
	else
		s = ft_strdup(str);
	res = ft_strwlen((int*)s);
	wlen = pr->w - res;
	fill = (ft_strchr(pr->f, '0')) ? '0' : ' ';
	while (wlen-- > 0 && !ft_strchr(pr->f, '-') && ++res)
		ft_putchar(fill);
	ft_putwstr((int*)s);
	while (wlen-- + 1 > 0 && ft_strchr(pr->f, '-') && ++res)
		ft_putchar(' ');
	free(s);
	return (res);
}
