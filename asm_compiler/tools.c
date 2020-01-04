/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:57:31 by nouhaddo          #+#    #+#             */
/*   Updated: 2020/01/03 23:31:37 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[18];

/*
**	--------------------------------------------------------------------------
**	l = 0 ignoring whitespace (tabulation and space)
** 	l = 1 ignor whitespace and comment
** 	l = 2 ignor comment, newlines and whitespace
**	--------------------------------------------------------------------------
*/

int				ft_ignor_comment_whitspaces(char *s, t_point *p, int l)
{
	while (s[p->x + p->z])
	{
		if (l == 2 && s[p->x + p->z] == ENDLINE_CHAR)
			*p = (t_point){0, p->y + 1, p->z + p->x + 1};
		else if (l > 0 && (s[p->x + p->z] == COMMENT_CHAR ||
												s[p->x + p->z] == NEW_CMT))
			p->x += ft_findchar(s + p->x + p->z, ENDLINE_CHAR);
		else if (ft_findchar(WHITESPACES, s[p->x + p->z]) != -1)
			p->x += skip_chars(s + p->x + p->z, WHITESPACES);
		else
			break ;
	}
	return (s[p->x + p->z] ? 1 : 0);
}

/*
**	--------------------------------------------------------------------------
**	free all spaced allocated during compiling of the file
**	--------------------------------------------------------------------------
*/

void			ft_free_used_mem(char *name, char *file, t_label *lab,
				t_inst *inst)
{
	t_label		*cur_lab;
	t_inst		*cur_inst;

	ft_free(name);
	ft_free(file);
	while (lab)
	{
		cur_lab = lab;
		lab = lab->next;
		ft_free(cur_lab->name);
		ft_free(cur_lab);
	}
	while (inst)
	{
		cur_inst = inst;
		inst = inst->next;
		ft_free(cur_inst->args[0]);
		ft_free(cur_inst->args[1]);
		ft_free(cur_inst->args[2]);
		ft_free(cur_inst);
	}
}

/*
**	--------------------------------------------------------------------------
**	initial variables
**	--------------------------------------------------------------------------
*/

int				ft_init(t_header *f, t_ptr *lst, t_point *p)
{
	ft_bzero(f, sizeof(t_header));
	if (!(lst[0].head = ft_malloc(sizeof(t_inst))))
		return ((int)ft_error("can't malloc insturction"));
	lst[0].tail = lst[0].head;
	if (!(lst[1].head = ft_malloc(sizeof(t_label))))
		return ((int)ft_error("can't malloc label"));
	lst[1].tail = lst[1].head;
	*p = (t_point){0, 1, 0};
	return (1);
}

/*
**	--------------------------------------------------------------------------
**	calcul bytes of instruction
**	--------------------------------------------------------------------------
*/

int				instruction_byte(t_inst *inst)
{
	int			bytes;
	char		shift;
	int			i;

	if (!inst)
		return (0);
	bytes = 1;
	bytes += g_op_tab[inst->opcode].argcode;
	i = 0;
	while (i < g_op_tab[inst->opcode].arg_nbr)
	{
		i++;
		shift = (inst->argcode >> (8 - (i * 2))) & 3;
		if (shift == REG_CODE)
			bytes += 1;
		else if (shift == IND_CODE)
			bytes += 2;
		else
			bytes += (g_op_tab[inst->opcode].sh ? 2 : 4);
	}
	return (bytes);
}

void			ft_print_inst_labs(t_inst *inst, t_label *lab)
{
	ft_putendl("print labels");
	while ((lab = lab->next))
		ft_printf("name[%s]--pc[%d]\n", lab->name, lab->pc);
	ft_putendl("print instructions");
	while ((inst = inst->next))
		ft_printf("line[%d]--opcode[%d]--args[%s],[%s],[%s]--pc[%d]\n",
		inst->line, inst->opcode, inst->args[0], inst->args[1], inst->args[2],
		inst->pc);
}
