/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:05:40 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/27 22:49:32 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H
# include "op.h"
# include "define.h"

typedef struct			s_arg
{
	char				arg1;
	char				arg2;
	char				arg3;
}						t_arg;

typedef struct			s_op
{
	char				code;
	const char			*name;
	char				arg_num;
	char				arg[3];
	short				waiting_cycle;
	_Bool				arg_code;
	_Bool				carry;
	int					size_dir;
	int					mod;
	int					op_type;
}						t_op;

typedef struct			s_op_component
{
	int					code;
	unsigned char		arg_code;
	int					arg[4];
	int					step;
}						t_op_component;

typedef struct			s_process
{
	int					prc_id;
	int					id_player;
	int					reg[REG_NUMBER + 1];
	_Bool				carry;
	int					pc;
	unsigned char		*memory;
	int					cycle;
	int					cycle_to_die;
	struct s_process	*next;
	t_op_component		cmp;
	_Bool				live;
}						t_process;

typedef struct			s_flag
{
	_Bool				dump;
	_Bool				v;
	_Bool				vs;
}						t_flag;

typedef struct			s_byte
{
	int					player;
	int					cp;
	int					status;
	char				content[3];
}						t_byte;

typedef struct			s_player
{
	t_header			header;
	char				*file;
	_Bool				full;
	int					live;
	char				prog[CHAMP_MAX_SIZE];
	unsigned char		source_code[SIZE_TOTAL];
}						t_player;

typedef struct			s_arena
{
	unsigned char		memory[MEM_SIZE];
	int					cycle;
	int					cycle_to_die;
	int					count_current_cycle;
	int					nbr_check;
	int					last_player_alive;
	int					nbr_live_current;
	int					nbr_process_alive;
	int					prc_last_id;
	int					dump_nb_cycles;
	t_process			*process;
}						t_arena;

typedef struct			s_vm
{
	t_arena				arena;
	t_player			player[4];
	t_op				op_tab[17];
	t_byte				bytes[64][64];
	t_flag				flag;
	int					player_file[4];
	int					winner;
	int					end_game;
	int					nb_players;
	int					visu_spd;
	char				visu_event;
	int					lifes[4];
}						t_vm;

#endif
