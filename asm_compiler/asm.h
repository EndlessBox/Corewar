/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 22:32:45 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/12/31 14:35:50 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H
# include "../libft/includes/libft.h"
# include "op.h"
# include <fcntl.h>

/*
**	--------------------------------------------------------------------------
**	TOKENS IDENTIFIERS
**	--------------------------------------------------------------------------
*/

# define CMD_CHAR '.'
# define SEP_CHAR ','
# define NEW_CMT ';'
# define ENDLINE_CHAR '\n'
# define STRING_CHAR '"'
# define WHITESPACES "\t "
# define NAME_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789-:"

/*
**	--------------------------------------------------------------------------
**	DEBUGGIN MODES
**	--------------------------------------------------------------------------
*/

# define DB1 ft_putstr(CYAN("HERE1\n"));
# define DB2 ft_putstr(CYAN("HERE2\n"));
# define DB3 ft_putstr(CYAN("HERE3\n"));
# define DB4 ft_putstr(CYAN("HERE4\n"));
# define DB5 ft_putstr(CYAN("HERE5\n"));
# define DB6 ft_putstr(CYAN("HERE6\n"));
# define DB7 ft_putstr(CYAN("HERE7\n"));

/*
**	--------------------------------------------------------------------------
**	ERROR DEFINES SHORTCUTS
**	--------------------------------------------------------------------------
*/

# define CMD_STRING "comand must be followed by string"
# define ENDLINE_ER "instruction must end with new line"
# define PROG_COMMENT_ER "invalid program comment"
# define PROG_NAME_ER "invalid program name"
# define CMD_ER "invalid command"
# define INST_ER "Invalid Instruction"
# define DUP_CMT_CMD "duplicated comment command"
# define DUP_NAME_CMD "duplicated name command"
# define DUP_LAB_ER "duplicated label"
# define PARAM_ER "invalid parameter"
# define PARAMS_ER "Invalid number of parameters"
# define READ_ER "An error occured while reading file"
# define PROG_SIZE_ER "Program size more then CHAMP_MAX_SIZE\n"
# define LABEL_CHARS_ER "Invalid label characters"
# define OPCODE_ER "invalid opcode"
# define SEP_ER "parameters must separate by comma"

/*
**	--------------------------------------------------------------------------
**	SHORTCUTS FUNCTIONS AND VARIABLES
**	--------------------------------------------------------------------------
*/

# define NAME_L ft_strlen(NAME_CMD_STRING)
# define CMT_L ft_strlen(COMMENT_CMD_STRING)
# define BTW BETWEEN
# define PUSH(type, tail, new) ((type)(tail))->next = new; tail = new
# define TOT_SIZE (f->prog_size + 16 + PROG_NAME_LENGTH + COMMENT_LENGTH)
# define F first
# define S second

typedef unsigned int	t_uint;
/*
**	--------------------------------------------------------------------------
**	SYNTAX ANALYSIS FUNCTIONS AND STRUCTS
**	--------------------------------------------------------------------------
*/

typedef struct			s_pair
{
	int					first;
	int					second;
}						t_pair;

typedef struct			s_inst
{
	int					opcode;
	t_arg_type			argcode;
	char				*args[3];
	int					line;
	int					pc;
	struct s_inst		*next;
}						t_inst;

typedef struct			s_label
{
	char				*name;
	int					pc;
	struct s_label		*next;
}						t_label;

int						ft_add_label(char *file, t_ptr *lst, t_point *p,
						int pc);
int						ft_direct_param(char *file, char **par, t_point *p,
						int l);
int						ft_get_param(char *file, char **par, t_point *p);
int						ft_add_instruction(char *file, int op, t_ptr *inst,
						t_point *p);
t_uint					read_instructions(t_point *p, char *file, t_ptr *lst,
											t_uint *pc);
/*
**	--------------------------------------------------------------------------
**	BYTE CODE TRANSLATE FUNCTIONS
**	--------------------------------------------------------------------------
*/

int						instruction_byte(t_inst *inst);
int						get_label_pc(t_label *lab, char *to_search,
						t_inst *inst, int *v);
int						add_bytes(char *mem, int bytes, int value);
int						write_to_exe(t_header *f, t_inst *inst, t_label *lab,
						char *name);
int						bytecode(t_inst *inst, t_label *lab, char *mem);

/*
**	--------------------------------------------------------------------------
**	function tools
**	--------------------------------------------------------------------------
*/

int						ft_init(t_header *f, t_ptr *lst, t_point *p);
void					*ft_print_error(int error, char *msg, t_point p);
int						ft_ignor_comment_whitspaces(char *s, t_point *p, int l);
void					ft_free_used_mem(char *name, char *file, t_label *lab,
						t_inst *inst);
void					ft_print_inst_labs(t_inst *inst, t_label *lab);

/*
**	--------------------------------------------------------------------------
**	struct for operations
**	--------------------------------------------------------------------------
*/

typedef struct			s_op
{
	char				*name;
	int					arg_nbr;
	char				arg[3];
	int					opcode;
	int					cycle;
	char				*desc;
	int					argcode;
	int					sh;
}						t_op;

#endif
