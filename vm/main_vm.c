/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:46:55 by souarrak          #+#    #+#             */
/*   Updated: 2020/01/03 23:29:00 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

void		print_players(t_player player[4], int nb_players)
{
	int	i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < nb_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				player[i].header.prog_size,
				player[i].header.prog_name,
				player[i].header.comment);
		i++;
	}
}

t_process	*create_process(t_vm *vm, t_player *palyer, int index)
{
	t_process *process;
	const int pc = index * MEM_SIZE / vm->nb_players;

	ft_memcpy(vm->arena.memory + pc, palyer->prog, palyer->header.prog_size);
	if (!(process = (t_process *)ft_memalloc(sizeof(t_process))))
		free_exit(vm);
	process->pc = pc;
	process->reg[1] = -(index + 1);
	process->memory = vm->arena.memory;
	process->id_player = -(index + 1);
	process->prc_id = vm->arena.prc_last_id++;
	vm->arena.nbr_process_alive++;
	return (process);
}

void		load_arena(t_vm *vm)
{
	int			i;
	int			j;
	t_process	*process;
	t_process	*ptr;

	i = -1;
	ptr = NULL;
	j = 0;
	while (++i < 4)
	{
		if (!vm->player[i].full)
			continue;
		process = create_process(vm, &vm->player[i], j);
		process->next = ptr;
		ptr = process;
		j++;
	}
	vm->arena.process = process;
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	init_all(&vm);
	get_input(argc, argv, &vm);
	if (vm.nb_players <= 0)
		return (-1);
	print_players(vm.player, vm.nb_players);
	load_arena(&vm);
	if (vm.flag.v)
		start_war_vs(&vm);
	else
		start_war(&vm);
	return (0);
}
