/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:08:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/27 22:51:53 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

void	logical_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 4)
		prc->reg[cmp->arg[2]] = cmp->arg[0] + cmp->arg[1];
	if (cmp->code == 5)
		prc->reg[cmp->arg[2]] = cmp->arg[0] - cmp->arg[1];
	if (cmp->code == 6)
		prc->reg[cmp->arg[2]] = cmp->arg[0] & cmp->arg[1];
	if (cmp->code == 7)
		prc->reg[cmp->arg[2]] = cmp->arg[0] | cmp->arg[1];
	if (cmp->code == 8)
		prc->reg[cmp->arg[2]] = cmp->arg[0] ^ cmp->arg[1];
	if (cmp->code == 9 && prc->carry)
		prc->pc = (prc->pc - 3) + (cmp->arg[0] % IDX_MOD);
	if (cmp->code == 16)
		ft_printf("Aff: %c\n", cmp->arg[0]);
}

void	fork_op(t_process *prc, t_op_component *cmp, t_vm *vm)
{
	t_process	*new;
	int			pc;

	if (prc->cmp.code == 12)
		pc = ADDR(prc->pc + cmp->arg[0] % IDX_MOD);
	else
		pc = ADDR(prc->pc + cmp->arg[0]);
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		free_exit(vm);
	ft_memcpy(new, prc, sizeof(t_process));
	new->pc = pc;
	new->prc_id = vm->arena.prc_last_id++;
	vm->arena.nbr_process_alive++;
	new->cycle = 0;
	new->next = vm->arena.process;
	vm->arena.process = new;
}

void	mem_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 3)
	{
		if ((cmp->arg_code >> 4 & 3) == REG_CODE)
			prc->reg[cmp->arg[1]] = cmp->arg[0];
		else
			set_mem(prc->memory, prc->pc + cmp->arg[1], cmp->arg[0], 4);
	}
	if (cmp->code == 11)
		set_mem(prc->memory, prc->pc + (cmp->arg[1] +
										cmp->arg[2]) % IDX_MOD, cmp->arg[0], 4);
	if (cmp->code == 2 || cmp->code == 13)
		prc->reg[cmp->arg[1]] = cmp->arg[0];
	if (cmp->code == 10)
		prc->reg[cmp->arg[2]] = get_mem(prc->memory,
										prc->pc + cmp->arg[0] + cmp->arg[1], 4);
	if (cmp->code == 14)
		prc->reg[cmp->arg[2]] = get_mem(prc->memory,
							prc->pc + (cmp->arg[0] + cmp->arg[1]) % IDX_MOD, 4);
}

int		live(t_vm *vm, t_process *prc)
{
	vm->arena.nbr_live_current++;
	prc->live = 1;
	if (BETWEEN(prc->cmp.arg[0], -4, -1))
	{
		vm->player[-prc->cmp.arg[0] - 1].live = vm->arena.cycle + 1;
		vm->winner = -prc->cmp.arg[0];
		vm->lifes[-prc->cmp.arg[0] - 1]++;
	}
	return (prc->cmp.arg[0]);
}

void	set_carry(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 2 || cmp->code == 3)
		prc->carry = prc->reg[cmp->arg[1]] == 0;
	else
		prc->carry = prc->reg[cmp->arg[2]] == 0;
}
