/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:53:23 by souarrak          #+#    #+#             */
/*   Updated: 2019/12/27 13:12:48 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

void	kill_process(t_vm *vm, t_process **process)
{
	t_process	*ptr;

	ptr = (*process)->next;
	free(*process);
	vm->arena.nbr_process_alive--;
	*process = ptr;
}

void	print_error(char *msg)
{
	ft_putendl(msg);
	exit(-1);
}

void	free_exit(t_vm *vm)
{
	t_process *ptr;

	ptr = vm->arena.process ? vm->arena.process->next : NULL;
	while (vm->arena.process)
	{
		ft_memdel((void **)&vm->arena.process);
		vm->arena.process = ptr;
		vm->arena.process ? ptr = vm->arena.process->next : 0;
	}
	exit(0);
}
