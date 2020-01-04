/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:45:11 by souarrak          #+#    #+#             */
/*   Updated: 2019/12/27 13:12:19 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

void	check_players(t_vm *vm, int id)
{
	int	fd;

	while (++id < 4)
	{
		if (!vm->player[id].full)
			continue;
		fd = open(vm->player[id].file, O_RDONLY);
		if (read(fd, vm->player[id].source_code, SIZE_TOTAL) <= 0)
			print_error("Error : Can't read source file");
		vm->player[id].header.magic = get_mem(vm->player[id].source_code, 0, 4);
		if (vm->player[id].header.magic != COREWAR_EXEC_MAGIC)
			print_error("Error : Header magic not compatible");
		vm->player[id].header.prog_size =
			get_mem(&vm->player[id].source_code[PROG_NAME_LENGTH + 8], 0, 4);
		if (vm->player[id].header.prog_size > CHAMP_MAX_SIZE
										|| vm->player[id].header.prog_size == 0)
			print_error("Error : source file > Size_Max or prog null");
		ft_memcpy(vm->player[id].prog, vm->player[id].source_code + HEADER_SIZE,
											vm->player[id].header.prog_size);
		ft_memcpy(vm->player[id].header.prog_name,
							vm->player[id].source_code + 4, PROG_NAME_LENGTH);
		ft_memcpy(vm->player[id].header.comment,
			vm->player[id].source_code + PROG_NAME_LENGTH + 12, COMMENT_LENGTH);
	}
}

void	install_players(t_vm *vm, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < vm->nb_players)
	{
		j = 0;
		if (vm->player_file[i] > 0)
			while (j < vm->nb_players)
			{
				if (!vm->player[j].full)
				{
					vm->player[j].file = argv[vm->player_file[i]];
					vm->player[j].full = TRUE;
					break ;
				}
				j++;
			}
		i++;
	}
}

int		set_player_id(t_vm *vm, int argc, char **argv, int i)
{
	int	id;

	if (vm->nb_players >= 4)
		print_error("Error : More than 4 players");
	if (ft_strequ(argv[i], "-n"))
	{
		if (i + 2 >= argc || !ft_isnbr(argv[i + 1]))
			print_error(USAGE);
		id = ft_atoi(argv[i + 1]);
		if (!BETWEEN(id, 1, 4))
			print_error("Error : The number of player must be between 1 and 4");
		if (vm->player[id - 1].full)
			print_error("Error : This number already token");
		vm->player[id - 1].file = argv[i + 2];
		vm->player[id - 1].full = TRUE;
		vm->nb_players++;
		return (2);
	}
	else
	{
		vm->player_file[vm->nb_players] = i;
		vm->nb_players++;
		return (0);
	}
}

void	get_input(int argc, char **argv, t_vm *vm)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "-dump") || argv[i][1] == 'd')
		{
			if (i + 1 >= argc || !ft_isnbr(argv[i + 1]))
				print_error(USAGE);
			vm->flag.dump = 1;
			vm->arena.dump_nb_cycles = ft_atoi(argv[i + 1]);
			i++;
		}
		else if (ft_strequ(argv[i], "-v"))
			vm->flag.v = 1;
		else
			i += set_player_id(vm, argc, argv, i);
	}
	install_players(vm, argv);
	check_players(vm, -1);
}
