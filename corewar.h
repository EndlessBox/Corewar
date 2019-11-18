/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:40:11 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/13 22:33:43 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "./libft/libft.h"
#include "./op.h"

# define FALSE  0
# define TRUE   1
# define DEB1   ft_putendl(CYAN("HERE 1"));
# define DEB2   ft_putendl(MAGENTA("HERE 2"));
# define DEB3   ft_putendl(BLUE("HERE 3"));

typedef enum			e_regs {
	r1, r2,
	r3, r4,
	r5, r6,
	r7, r8,
	r9, r10,
	r11, r12,
	r13, r14,
	r15, r16
}						t_regs;

typedef struct			s_process
{
	int					id;
	int					carry;
	void				*current_op;
	int					last_live_performed;
	int					cycle_before_exec;
	int					bytes_to_next_op;
	void				*registers;
	struct s_process	*next;

}						t_process;

typedef struct			s_player
{
	int					id;
	void				*name;
	char				*comment;
	int					exec_size;
	int					*exec_code;
	struct s_player		*next;
	struct s_player		*previous;
}						t_player;

typedef struct			s_monitor
{
	void				*last_pl_alive;
	int					cycle_counter;
	int					cycle_to_die;
	int					prev_ctd_lives;
	int					program_counter;
	int					check_performed;
}						t_monitor;

typedef struct			s_queue
{
	t_addr				*first;
	t_addr				*last;
}						t_queue;

typedef struct 			s_op
{
	char				*op_name;
	int					something_idont_know;
	int					op_args_type[3];
	int					op_id;
	int					op_cycle_to_execute;
	char				*description;
	int					something_i_dont_know2;
	int					maybe_modify_carry;
}						t_op;


/*
 *              Read size bytes from the given file descriptor.
 */

unsigned int            ft_read_file(int fd, size_t size);

/*
 *              Check And Extract players information.
 */

void					get_check_header(int fd);
int						check_0x0(int fd);
void					*get_check_name(int fd);
void					*get_champ_comment(int fd);
void					*get_check_exec(int fd, int exec_size);
t_player				*get_players(char **argv, int argc, int *players_number);
void					players_introduction(t_player *players);

/*
 *              Allocate the arena and place the players executable code
 *              in every player memory space.
 */

void					*initialize_map(t_player *players, int number);
unsigned int			ft_read_arena(unsigned int *arena, size_t size);

/*
 *              init_monitor : initialize the monitor of the game that keep track
 *              of number of cylces since the start and last player alive ....
 *              lst_player  : give you the last player.
 * 				check_still_alive : kill every process that didn't declare
 * 				himself alive during last cycle_to_die
 */

t_monitor				*init_monitor(t_player *players);
void					*last_player(t_player *players);
void        			check_still_alive(t_queue *queue, int curr_cycle);

/*
 *              Process init and management.
 */

t_process				*make_process(void);
t_queue					*make_affect_process(void *arena, t_player   *players, int players_nbr);

/*
 *				Queue functions
 */

t_queue					*ft_new_queue(void);
void					ft_enque(t_queue *q, void *data);
void					ft_pop(t_queue *q, t_addr *to_pop);
int						ft_free_queue(t_queue *q);

/*
 *              DEBUGGING FUNCTION
 */

void					DB_show_players(t_player *player, int norm_rev);
void					DB_show_arena(void *arena);
void					DB_show_monitor(t_monitor *monitor);
void					DB_show_queue(t_queue  *queue);

#endif
