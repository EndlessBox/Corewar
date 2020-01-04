/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:32:47 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/27 13:14:38 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

static void	dump_hex(unsigned char *memory)
{
	const char	*tab = "0123456789abcdef";
	int			i;

	i = 0;
	while (i < MAX_DUMP)
	{
		ft_printf("%c", tab[memory[i] / 16]);
		ft_printf("%c", tab[memory[i] % 16]);
		i < MAX_DUMP - 1 ? ft_printf(" ") : 0;
		i++;
	}
	ft_printf(" \n");
}

void		dump_arena(unsigned char *memory, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		i == 0 ? ft_printf("0x0000 : ") : ft_printf("%#.4x : ", i);
		dump_hex(memory + i);
		i += MAX_DUMP;
	}
}

int			get_mem(unsigned char *mem, int addr, int oct)
{
	long	ret;
	int		i;

	i = 0;
	ret = 0;
	while (i < oct)
	{
		ret = (ret << 8) + mem[ADDR(addr + i)];
		i++;
	}
	if (ret >= 1 << (oct * 8 - 1))
		ret = -(((long)1 << (oct * 8)) - ret);
	return (ret);
}

void		set_mem(unsigned char *mem, int addr, int val, int oct)
{
	int	i;

	i = 0;
	if (val < 0)
		val = ((long)1 << (oct * 8)) + (long)val;
	while (i < oct)
	{
		mem[ADDR(addr + i)] = val >> ((oct - i - 1) * 8);
		i++;
	}
}
