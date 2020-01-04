/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:46:29 by nouhaddo          #+#    #+#             */
/*   Updated: 2020/01/03 23:30:24 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op	g_op_tab[18];

/*
**	--------------------------------------------------------------------------
**	check type of parameter and store it in param.
**	return value : param code size or 0 for error
**	--------------------------------------------------------------------------
*/

int				ft_direct_param(char *file, char **par, t_point *p, int l)
{
	p->x += l + 1;
	ft_ignor_comment_whitspaces(file, p, 0);
	if ((*par)[0] == LABEL_CHAR)
	{
		return ((skip_chars(*par + 1, LABEL_CHARS) != (int)ft_strlen(*par
		+ 1)) ? (int)ft_print_error(3, LABEL_CHARS_ER, *p) : DIR_CODE);
	}
	return ((ft_isnumber(*par)) ? DIR_CODE : (int)ft_print_error(3,
	PARAM_ER, *p));
}

int				ft_get_param(char *file, char **par, t_point *p)
{
	int			l;

	ft_ignor_comment_whitspaces(file, p, 0);
	l = skip_chars(file + p->x + p->z +
					(file[p->x + p->z] == DIRECT_CHAR ? 1 : 0), NAME_CHARS);
	if (!(*par = ft_strndup(file + p->x + p->z +
							(file[p->x + p->z] == DIRECT_CHAR ? 1 : 0), l)))
		return ((int)ft_error("Can't malloc for parameter"));
	if (file[p->x + p->z] == DIRECT_CHAR)
		return (ft_direct_param(file, par, p, l));
	p->x += l;
	ft_ignor_comment_whitspaces(file, p, 0);
	if ((*par)[0] == LABEL_CHAR)
	{
		return ((skip_chars(*par + 1, LABEL_CHARS) != (int)ft_strlen(*par + 1))
		? (int)ft_print_error(3, LABEL_CHARS_ER, *p) : IND_CODE);
	}
	if ((*par)[0] == 'r')
	{
		return ((ft_isnumber(*par + 1) && BTW(ft_atoi(*par + 1), 1, REG_NUMBER))
		? REG_CODE : (int)ft_print_error(3, PARAM_ER, *p));
	}
	return ((ft_isnumber(*par)) ? IND_CODE : (int)ft_print_error(3, PARAM_ER,
		*p));
}

/*
**	--------------------------------------------------------------------------
**	Calcul instruction size in bytes
**	--------------------------------------------------------------------------
*/

int				ft_add_instruction(char *file, int op, t_ptr *inst, t_point *p)
{
	t_inst		*new;
	int			t;
	int			i;

	if (!(new = ft_malloc(sizeof(t_inst))))
		return ((int)ft_error("can't malloc for instruction"));
	i = 0;
	while (op && i < g_op_tab[op].arg_nbr)
	{
		if (!((t = ft_get_param(file, &new->args[i], p)) & g_op_tab[op].arg[i]))
			op = (int)ft_print_error(2, PARAM_ER, *p);
		new->argcode |= ((char)t) << (8 - (++i * 2));
		if (op && i < g_op_tab[op].arg_nbr && file[p->x + p->z] != SEP_CHAR)
			op = (int)ft_print_error(2, SEP_ER, *p);
		(op && i < g_op_tab[op].arg_nbr) ? p->x++ : 0;
	}
	new->line = p->y;
	new->opcode = op;
	PUSH(t_inst*, inst->tail, new);
	ft_ignor_comment_whitspaces(file, p, 1);
	if (op && i != g_op_tab[op].arg_nbr)
		op = (int)ft_print_error(2, PARAMS_ER, *p);
	if (op && file[p->x + p->z] != ENDLINE_CHAR)
		op = (int)ft_print_error(2, ENDLINE_ER, *p);
	return (op);
}

/*
**	--------------------------------------------------------------------------
**	add label new label
**	--------------------------------------------------------------------------
*/

int				ft_add_label(char *file, t_ptr *lst, t_point *p, int pc)
{
	char		*name;
	t_label		*cur;
	int			lab_len;

	lab_len = skip_chars(file + p->x + p->z, LABEL_CHARS);
	if (!(name = ft_strndup(file + p->x + p->z, lab_len)))
		return ((int)ft_error("Can't malloc for label name"));
	cur = lst[1].head;
	while ((cur = cur->next))
		if (!strcmp(name, cur->name))
		{
			ft_free(name);
			return ((int)ft_print_error(2, DUP_LAB_ER, *p));
		}
	p->x += lab_len + 1;
	if (!(cur = (t_label*)ft_malloc(sizeof(t_label))))
		return ((int)ft_error("Can't malloc for label"));
	cur->name = name;
	cur->pc = pc;
	((t_label*)lst[1].tail)->next = cur;
	lst[1].tail = cur;
	ft_ignor_comment_whitspaces(file, p, 1);
	if (!file[p->x + p->z])
		return ((int)ft_print_error(2, ENDLINE_ER, *p));
	return (1);
}

/*
**	--------------------------------------------------------------------------
**	check inputs and decide it's label or instruction otherwise error
**	--------------------------------------------------------------------------
*/

t_uint			read_instructions(t_point *p, char *file, t_ptr *lst,
				t_uint *pc)
{
	int			i;
	int			l;

	while (ft_ignor_comment_whitspaces(file, p, 2))
	{
		l = skip_chars(file + p->x + p->z, LABEL_CHARS);
		if (file[p->x + p->z + l] == LABEL_CHAR)
		{
			if (!ft_add_label(file, lst, p, *pc))
				return (0);
			continue ;
		}
		i = 1;
		while (i < 17 && ft_strncmp(file + p->x + p->z, g_op_tab[i].name, l))
			i++;
		p->x += l;
		if (i == 17)
			return ((int)ft_print_error(3, OPCODE_ER, *p));
		if (!ft_add_instruction(file, i, &lst[0], p))
			return (0);
		((t_inst*)lst[0].tail)->pc = *pc;
		*pc += instruction_byte(lst[0].tail);
	}
	return (*pc);
}
