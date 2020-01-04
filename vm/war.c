/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:47:50 by souarrak          #+#    #+#             */
/*   Updated: 2019/12/28 01:42:01 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

static void	check_arena(t_vm *vm)
{
	t_process	**process;

	if (vm->arena.count_current_cycle != vm->arena.cycle_to_die)
		return ;
	vm->arena.count_current_cycle = 0;
	vm->arena.nbr_check++;
	process = &vm->arena.process;
	while (*process)
	{
		if (!(*process)->live)
		{
			kill_process(vm, process);
			continue;
		}
		else
			(*process)->live = FALSE;
		process = &(*process)->next;
	}
	if (vm->arena.nbr_live_current >= NBR_LIVE ||
		vm->arena.nbr_check == MAX_CHECKS)
	{
		vm->arena.cycle_to_die -= CYCLE_DELTA;
		vm->arena.nbr_check = 0;
	}
	vm->arena.nbr_live_current = 0;
}

void		exec_op(t_vm *vm, t_process *prc)
{
	if (vm->op_tab[prc->cmp.code].op_type == 1)
		logical_op(prc, &prc->cmp);
	else if (vm->op_tab[prc->cmp.code].op_type == 2)
		fork_op(prc, &prc->cmp, vm);
	else if (vm->op_tab[prc->cmp.code].op_type == 3)
		mem_op(prc, &prc->cmp);
	else
		live(vm, prc);
	vm->op_tab[prc->cmp.code].carry ? set_carry(prc, &prc->cmp) : 0;
	prc->pc = ADDR(prc->pc + prc->cmp.step);
}

void		exe_cycle(t_vm *vm)
{
	t_process	*prc;

	prc = vm->arena.process;
	while (prc)
	{
		prc->pc = ADDR(prc->pc);
		if (prc->cycle == 0)
			set_op_code(prc, vm);
		if (prc->cycle > 0)
			prc->cycle--;
		if (prc->cycle == 0)
		{
			if (BETWEEN(prc->cmp.code, 1, 16) && parse_operation(vm, prc))
				exec_op(vm, prc);
			else if (BETWEEN(prc->cmp.code, 1, 16))
				prc->pc = ADDR(prc->pc + get_op_size(vm, prc));
			else
				prc->pc = ADDR(prc->pc + 1);
		}
		prc = prc->next;
	}
}

void		start_war(t_vm *vm)
{
	while (vm->arena.cycle_to_die > 0 && vm->arena.nbr_process_alive > 0)
	{
		check_arena(vm);
		exe_cycle(vm);
		vm->arena.count_current_cycle++;
		vm->arena.cycle++;
		if (vm->flag.dump && vm->arena.dump_nb_cycles == vm->arena.cycle)
		{
			dump_arena(vm->arena.memory, MEM_SIZE);
			free_exit(vm);
		}
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->winner,
								vm->player[vm->winner - 1].header.prog_name);
	free_exit(vm);
}

void		start_war_vs(t_vm *vm)
{
	void	*scr;

	scr = init_vis();
	vm_vis(vm, 0, scr);
	while (vm->arena.cycle_to_die > 0 && vm->arena.nbr_process_alive > 0)
	{
		check_arena(vm);
		exe_cycle(vm);
		vm->arena.count_current_cycle++;
		vm->arena.cycle++;
		if (vm->flag.dump && vm->arena.dump_nb_cycles == vm->arena.cycle)
		{
			dump_arena(vm->arena.memory, MEM_SIZE);
			free_exit(vm);
		}
		vm_vis(vm, 1, scr);
	}
	vm->end_game = 1;
	vm_vis(vm, -1, scr);
	getch();
	endwin();
	free_exit(vm);
}
