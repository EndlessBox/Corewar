/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:28:22 by souarrak          #+#    #+#             */
/*   Updated: 2019/12/28 01:39:48 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

static void	init_arena(t_vm *vm)
{
	int i;

	i = -1;
	vm->arena.cycle = 0;
	vm->arena.nbr_process_alive = 0;
	vm->arena.count_current_cycle = 0;
	vm->arena.cycle_to_die = CYCLE_TO_DIE;
	vm->arena.last_player_alive = 0;
	vm->arena.nbr_check = 0;
	vm->arena.prc_last_id = 1;
	vm->arena.nbr_live_current = 0;
	vm->arena.dump_nb_cycles = 0;
	vm->arena.process = NULL;
	vm->visu_spd = 50000;
	vm->visu_event = 'x';
	vm->winner = 0;
	vm->end_game = 0;
	while (++i < 4)
		vm->lifes[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
		vm->arena.memory[i] = 0;
}

static void	init_players(t_vm *vm)
{
	int i;

	i = 0;
	while (i < 4)
	{
		vm->player[i].full = FALSE;
		vm->player[i].live = 0;
		i++;
	}
}

void		init_all(t_vm *vm)
{
	init_arena(vm);
	init_players(vm);
	init_op_tab(vm->op_tab);
	vm->nb_players = 0;
	vm->flag.dump = FALSE;
	vm->flag.v = FALSE;
	vm->flag.vs = TRUE;
}
