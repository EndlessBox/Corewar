/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:14:11 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/12/30 21:20:37 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_op_tab[18];

/*
**	--------------------------------------------------------------------------
**	print error mode syntax error or tokenize error, with corrdination of error
**	and SUGGESTION sometimes.
**	--------------------------------------------------------------------------
*/

void		*ft_print_error(int error, char *msg, t_point p)
{
	if (error == 1)
		ft_putstr(RED("GLOABLE ERROR : "));
	else if (error == 2)
		ft_putstr(RED("SYNTAX ERROR : "));
	else if (error == 3)
		ft_putstr(RED("LEXICAL ERROR : "));
	ft_printf("[line : %d | colone %d]\n", p.y, p.x + 1);
	if (msg)
	{
		ft_putstr(CYAN("SUGGESTION : "));
		ft_putendl(msg);
	}
	return (NULL);
}

/*
**	--------------------------------------------------------------------------
**	SEARCH FOR LABEL AND RETURN IT'S PC, OTHERWISE PRINT ERROR AND RETURN 0.
**	--------------------------------------------------------------------------
*/

int			get_label_pc(t_label *lab, char *to_search, t_inst *inst, int *v)
{
	while ((lab = lab->next))
		if (ft_strcmp(lab->name, to_search) == 0)
		{
			*v = lab->pc - inst->pc;
			return (1);
		}
	ft_print_error(2, "label not found", (t_point){0, inst->line, 0});
	return (0);
}

/*
**	--------------------------------------------------------------------------
**	PRINT BYTES TO MEMORY WITH RIGHT ENCODE BIG ENDIAN
**	--------------------------------------------------------------------------
*/

int			add_bytes(char *mem, int bytes, int value)
{
	int		i;
	int		j;

	j = bytes;
	i = 0;
	while (i < bytes)
		mem[i++] = ((char*)(&value))[--j];
	return (bytes);
}

/*
**	--------------------------------------------------------------------------
**	LOOP TROUGH INSTRUCTIONS AND TRANSFER IT TO BYTES THEN WRITE IT TO MEM
**	--------------------------------------------------------------------------
*/

int			bytecode(t_inst *inst, t_label *lab, char *mem)
{
	int		i;
	int		j;
	int		v;

	i = 0;
	while ((inst = inst->next))
	{
		mem[i++] = (char)inst->opcode;
		(g_op_tab[inst->opcode].argcode) ? mem[i++] = (char)inst->argcode : 0;
		j = 0;
		while (j < g_op_tab[inst->opcode].arg_nbr && inst->args[j])
		{
			v = ft_atoi(inst->args[j] + (inst->args[j][0] == 'r' ? 1 : 0));
			if (inst->args[j][0] == ':' && !get_label_pc(lab, inst->args[j] + 1,
				inst, &v))
				return (0);
			if ((inst->argcode >> (8 - (++j * 2)) & 3) == REG_CODE)
				mem[i++] = (char)v;
			else if ((inst->argcode >> (8 - (j * 2)) & 3) == IND_CODE)
				i += add_bytes(mem + i, 2, v);
			else
				i += add_bytes(mem + i, (g_op_tab[inst->opcode].sh) ? 2 : 4, v);
		}
	}
	return (1);
}

/*
**	--------------------------------------------------------------------------
**	CONSTRUCT THE FINAL BYTECODE FILE
**	--------------------------------------------------------------------------
*/

int			write_to_exe(t_header *f, t_inst *inst, t_label *lab, char *name)
{
	char	exe[TOT_SIZE];
	int		i;
	int		fd;

	i = 0;
	ft_bzero(exe, TOT_SIZE);
	if (f->prog_size > CHAMP_MAX_SIZE)
	{
		return ((int)ft_print_error(1, "champ size is too large",
					(t_point){0, 0, 0}));
	}
	i += add_bytes(exe + i, 4, COREWAR_EXEC_MAGIC);
	ft_strcpy(exe + i, f->prog_name);
	i += PROG_NAME_LENGTH + 4;
	i += add_bytes(exe + i, 4, f->prog_size);
	ft_strcpy(exe + i, f->comment);
	i += COMMENT_LENGTH + 4;
	if (!bytecode(inst, lab, exe + i))
		return (0);
	if (!(fd = open(name, O_WRONLY | O_CREAT, 0644)))
		return (0);
	if (write(fd, exe, TOT_SIZE) < 0)
		return ((int)ft_error("an error occured while writting bytes to file"));
	ft_printf("Writing output program to %s\n", name);
	return (1);
}
