/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:17:13 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/04 00:00:45 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

static int		get_tdir(t_vm *vm, t_process *prc, int pc)
{
	return (get_mem(prc->memory, pc, vm->op_tab[prc->cmp.code].size_dir));
}

static int		get_tind(t_vm *vm, t_process *prc, int pc)
{
	int	addr;

	addr = get_mem(prc->memory, pc, 2);
	if (prc->cmp.code == 3)
		return (addr % IDX_MOD);
	if (vm->op_tab[prc->cmp.code].mod)
		return (get_mem(prc->memory, prc->pc + addr % IDX_MOD, 4));
	else
		return (get_mem(prc->memory, prc->pc + addr, 4));
}

static _Bool	get_reg(t_process *prc, int pc, int arg)
{
	static const int op_need_reg_addr1[] = {0, 0, 2, 3, 0, 0, 0, 0, 0,
													0, 0, 0, 0, 13, 0, 0, 0};
	static const int op_need_reg_addr2[] = {0, 0, 0, 0, 4, 5, 6, 7, 8,
													0, 10, 0, 0, 0, 14, 0, 0};

	pc = ADDR(pc);
	if (prc->memory[pc] > 16 || prc->memory[pc] < 1)
		return (0);
	if (op_need_reg_addr1[prc->cmp.code] && arg == 1)
		prc->cmp.arg[arg] = prc->memory[pc];
	else if (op_need_reg_addr2[prc->cmp.code] && arg == 2)
		prc->cmp.arg[arg] = prc->memory[pc];
	else
		prc->cmp.arg[arg] = prc->reg[prc->memory[pc]];
	return (1);
}

static int		get_arg(t_vm *vm, t_process *prc, int code)
{
	int i;
	int argc;

	i = 0;
	prc->cmp.arg_code = prc->memory[ADDR(prc->pc + 1)];
	while (i < vm->op_tab[code].arg_num)
	{
		argc = (prc->cmp.arg_code >> (6 - i * 2) & 3);
		argc += argc == 3;
		if (vm->op_tab[code].arg[i] & argc)
		{
			if (argc == T_DIR)
				prc->cmp.arg[i] = get_tdir(vm, prc, prc->pc + prc->cmp.step);
			if (argc == T_IND)
				prc->cmp.arg[i] = get_tind(vm, prc, prc->pc + prc->cmp.step);
			else if (argc == T_REG && !get_reg(prc, prc->pc + prc->cmp.step, i))
				return (0);
		}
		else
			return (0);
		prc->cmp.step += argc != T_DIR ? 1 + (argc == T_IND) :
													vm->op_tab[code].size_dir;
		i++;
	}
	return (1);
}

_Bool			parse_operation(t_vm *vm, t_process *prc)
{
	if (!vm->op_tab[prc->cmp.code].arg_code)
	{
		prc->cmp.step = 1 + vm->op_tab[prc->cmp.code].size_dir;
		prc->cmp.arg[0] = get_mem(prc->memory, prc->pc + 1, prc->cmp.step - 1);
		return (TRUE);
	}
	prc->cmp.step = 2;
	if (get_arg(vm, prc, prc->cmp.code))
		return (TRUE);
	return (FALSE);
}
