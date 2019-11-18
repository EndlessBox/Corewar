/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_players_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:58:31 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/13 22:00:52 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			players_introduction(t_player *players)
{
	t_player	*temp;

	temp = players;
	ft_printf("Introducing contestants...\n");
	while (temp)
	{
		ft_printf("Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", temp->id,
			temp->exec_size, temp->name, temp->comment);
		temp = temp->next;
	}
}

t_player		*get_players(char **argv, int argc, int *number)
{
	int			jumper;
	int			hopper;
	t_player	*player;
	t_player	*temp;
	int			fd;

	if (argc > 5 || argc < 2)
		ft_error("INCORRECT NUMBER OF ARGUMENTS");
	hopper = 0;
	if (!(player = (t_player*)malloc(sizeof(t_player))))
		ft_error("ALLOCATION ERROR");
	player->previous = NULL;
	temp = player;
	while (++hopper < argc)
	{
		fd = open(argv[hopper], O_RDONLY);
		get_check_header(fd);
		temp->id = hopper;
		(*number)++;
		temp->name = get_check_name(fd);
		temp->exec_size = ft_read_file(fd, 4);
		temp->comment = get_champ_comment(fd);
		if (!check_0x0(fd))
			ft_error("NAME DONT END WITH 0x0");
		temp->exec_code = get_check_exec(fd, temp->exec_size);
		if (hopper + 1 < argc)
		{
			if (!(temp->next = (t_player*)malloc(sizeof(t_player))))
				ft_error("ALLOCATION ERROR");
			temp->next->previous  = temp;
		}
		else
		{
			temp->next = NULL;
			break ;
		}
		temp = temp->next;
	}
	return (player);
}
