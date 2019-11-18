/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:37:36 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/11 14:01:34 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./corewar.h"

unsigned int    ft_read_file(int fd, size_t size)
{
	unsigned char	data[size];
	int				jumper;
	unsigned int	result;

	jumper = -1;
	result = 0;
	if (!(read(fd,&data, size) > 0))
		return (0);
	while (++jumper < size)
		result = result << 8 | data[jumper];
	return (result);
}

unsigned int    ft_read_arena(unsigned int *arena, size_t size)
{
	unsigned char   data[size];
	int             jumper;
	unsigned int    result;

	jumper = -1;
	result = 0;
	while (++jumper < size)
		data[jumper] = arena[jumper] & 0xff;
	jumper = -1;
	result = result | data[++jumper];
	while (++jumper < size)
		result = result << 8 | data[jumper];
	return (result);
}

void   get_check_header(int fd)
{
	unsigned int result;

	result = ft_read_file(fd, 4);
	if (result != COREWAR_EXEC_MAGIC)
		ft_error("BAD HEADER !");
}

void    *get_check_name(fd)
{
	int     jumper;
	void    *champ_name;

	if (!(champ_name = malloc(128)))
		ft_error("NAME ALLOCATION ERROR");
	jumper = 0;
	while (jumper < 128)
	{
		((char*)champ_name)[jumper] = ft_read_file(fd, 1);
		jumper++;
	}
	if (!check_0x0(fd))
		ft_error("NAME DONT END WITH 0x0");
	return (champ_name);
}

void    *get_champ_comment(int fd)
{
	void    *champ_comment;
	int     jumper;

	champ_comment = ft_strnew(2048);
	jumper = 0;
	while (jumper < 2048)
	{
		((char*)champ_comment)[jumper] = ft_read_file(fd, 1);
		jumper++;
	}
	return (champ_comment);
}

void     *get_check_exec(int fd, int exec_size)
{
	void     *champ_exec;
	int     jumper;

	champ_exec = (int*)malloc(sizeof(int) * exec_size);
	jumper = -1;
	while (++jumper < CHAMP_MAX_SIZE && jumper < exec_size)
		((int*)champ_exec)[jumper] = ft_read_file(fd, 1);
	if (jumper != exec_size)
		ft_error("Error player executable size dont matche the real player size");
	return (champ_exec);
}

int     check_0x0(int fd)
{
	if (!ft_read_file(fd, 4))
		return (1);
	return (0);
}
