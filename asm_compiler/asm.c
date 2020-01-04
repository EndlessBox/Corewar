/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 10:44:19 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/12/31 14:03:26 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	--------------------------------------------------------------------------
**	check existence of file then extension
**  read the content of file and save it in file_content
**  return value : NULL for an error occured otherwise new name of file .cor
**	--------------------------------------------------------------------------
*/

char			*check_file(char *file, char **file_content)
{
	int			fd;
	char		*extension;
	char		*name;
	char		*temp;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error("File not exist"));
	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".s") != 0)
		return (ft_error("Invalid File extension"));
	if (!ft_prot(temp = ft_strndup(file, (int)extension - (int)file)))
		return (NULL);
	name = ft_strjoin(temp, ".cor");
	ft_free(temp);
	if (!name)
		return (NULL);
	if (!(*file_content = ft_get_file_content(fd, BUFF_SIZE)))
	{
		ft_free(name);
		ft_error(READ_ER);
	}
	return (name);
}

/*
**	--------------------------------------------------------------------------
**	check the general format for the string (it can be program name or comment)
**  return value : 0 for an error occured otherwise 1
**	--------------------------------------------------------------------------
*/

int				set_string(char *file, char *dst, int max_len, t_point *p)
{
	ft_ignor_comment_whitspaces(file, p, 0);
	if (file[p->x + p->z] != STRING_CHAR)
		return ((int)ft_print_error(1, CMD_STRING, *p));
	*p = (t_point){0, p->y, p->z + 1 + p->x};
	while (file[p->x + p->z] && file[p->x + p->z] != STRING_CHAR)
		if (file[p->x++ + p->z] == ENDLINE_CHAR)
			p->y++;
	if (file[p->x + p->z] == STRING_CHAR && p->x <= max_len)
		ft_strncpy(dst, file + p->z, p->x);
	else
	{
		if (p->x <= max_len)
			return ((int)ft_print_error(1, "Invalid string", *p));
		else
			return ((int)ft_print_error(1, (max_len == COMMENT_LENGTH) ?
				PROG_COMMENT_ER : PROG_NAME_ER, *p));
	}
	p->x++;
	ft_ignor_comment_whitspaces(file, p, 1);
	if (file[p->x + p->z] != ENDLINE_CHAR)
		return ((int)ft_print_error(1, ENDLINE_ER, *p));
	return (1);
}

/*
**	--------------------------------------------------------------------------
**	read program name and comment
**  return value : 0 for an error occured otherwise 1
**	--------------------------------------------------------------------------
*/

int				ft_read_program_info(char *file, t_header *f, t_point *p)
{
	t_pair		b;

	b = (t_pair){0, 0};
	while (ft_ignor_comment_whitspaces(file, p, 2) && (!b.first || !b.second))
	{
		if (!ft_strncmp(file + p->x + p->z, NAME_CMD_STRING, NAME_L))
		{
			if (b.F)
				return ((int)ft_print_error(1, DUP_NAME_CMD, *p));
			p->x += NAME_L;
			if (!(b.F = set_string(file, f->prog_name, PROG_NAME_LENGTH, p)))
				return (0);
		}
		else if (!ft_strncmp(file + p->x + p->z, COMMENT_CMD_STRING, CMT_L))
		{
			if (b.S)
				return ((int)ft_print_error(1, DUP_CMT_CMD, *p));
			p->x += CMT_L;
			if (!(b.S = set_string(file, f->comment, COMMENT_LENGTH, p)))
				return (0);
		}
		else
			return ((int)ft_print_error(1, CMD_ER, *p));
	}
	return (1);
}

/*
**	--------------------------------------------------------------------------
**	main function do all necessary steps for compile asm code to bytecode
**  step 1 : check file extension the read file content
**  step 2 : read global info name and cooment of the player
**	step 3 : read instruction and label
**	step 4 : translate instruciont to bytes then write them to file.cor
**	--------------------------------------------------------------------------
*/

int				main(int ac, char **av)
{
	t_header	f;
	char		*file;
	char		*name;
	t_point		p;
	t_ptr		lst[2];

	if (ac <= 1)
		ft_printf("%sasm file.s [file ...]\n", MAGENTA("usage: "));
	else
		while (--ac)
		{
			ft_init(&f, lst, &p);
			if ((name = check_file(av[ac], &file)))
				if (ft_read_program_info(file, &f, &p))
					if (read_instructions(&p, file, lst, &f.prog_size))
						write_to_exe(&f, lst[0].head, lst[1].head, name);
			ft_free_used_mem(name, file, lst[1].head, lst[0].head);
		}
	return (0);
}
