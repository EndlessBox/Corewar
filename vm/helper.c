/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:28:26 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/27 13:13:18 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

/*
** op_code | name | arg number | arg type | waiting cycle | arg code |
** carry | dir size | modulo | op type
*/

void	init_op_tab(t_op *op)
{
	op[1] = (t_op){1, "live", 1, {T_DIR}, 10, 0, 0, 4, 0, 0};
	op[2] = (t_op){2, "ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 1, 4, 1, 3};
	op[3] = (t_op){3, "st", 2, {T_REG, T_IND | T_REG}, 5, 1, 0, 4, 1, 3};
	op[4] = (t_op){4, "add", 3, {T_REG, T_REG, T_REG}, 10, 1, 1, 4, 1, 1};
	op[5] = (t_op){5, "sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 1, 4, 1, 1};
	op[6] = (t_op){6, "and", 3, {T_REG | T_DIR | T_IND,
							T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1, 4, 1, 1};
	op[7] = (t_op){7, "or", 3, {T_REG | T_IND | T_DIR,
							T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1, 4, 1, 1};
	op[8] = (t_op){8, "xor", 3, {T_REG | T_IND | T_DIR,
							T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1, 4, 1, 1};
	op[9] = (t_op){9, "zjmp", 1, {T_DIR}, 20, 0, 0, 2, 0, 1};
	op[10] = (t_op){10, "ldi", 3, {T_REG | T_DIR | T_IND,
									T_DIR | T_REG, T_REG}, 25, 1, 0, 2, 1, 3};
	op[11] = (t_op){11, "sti", 3, {T_REG, T_REG | T_DIR | T_IND,
											T_DIR | T_REG}, 25, 1, 0, 2, 1, 3};
	op[12] = (t_op){12, "fork", 1, {T_DIR}, 800, 0, 0, 2, 1, 2};
	op[13] = (t_op){13, "lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 1, 4, 0, 3};
	op[14] = (t_op){14, "lldi", 3, {T_REG | T_DIR | T_IND,
									T_DIR | T_REG, T_REG}, 50, 1, 1, 2, 1, 3};
	op[15] = (t_op){15, "lfork", 1, {T_DIR}, 1000, 0, 0, 2, 0, 2};
	op[16] = (t_op){16, "aff", 1, {T_REG}, 2, 1, 0, 4, 0, 1};
}

int		get_op_size(t_vm *vm, t_process *prc)
{
	int ret;
	int i;
	int argc;
	int shift;

	ret = 1 + vm->op_tab[prc->cmp.code].arg_code;
	i = 0;
	if (!vm->op_tab[prc->cmp.code].arg_code)
		ret += vm->op_tab[prc->cmp.code].size_dir;
	else
	{
		shift = 8 - (vm->op_tab[prc->cmp.code].arg_num * 2);
		while (i < vm->op_tab[prc->cmp.code].arg_num)
		{
			argc = prc->cmp.arg_code >> (i * 2 + shift) & 3;
			if (argc == REG_CODE)
				ret += 1;
			else if (argc == DIR_CODE)
				ret += vm->op_tab[prc->cmp.code].size_dir;
			else if (argc == IND_CODE)
				ret += 2;
			i++;
		}
	}
	return (ret);
}

void	set_op_code(t_process *prc, t_vm *vm)
{
	prc->cmp.code = prc->memory[prc->pc];
	if (BETWEEN(prc->memory[prc->pc], 1, 16))
		prc->cycle = vm->op_tab[prc->cmp.code].waiting_cycle;
}
