/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 12:28:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/12/28 02:19:28 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "struct.h"
# include "../../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <ncurses.h>

void	init_all(t_vm *vm);
void	init_op_tab(t_op *op);
void	get_input(int argc, char **argv, t_vm *vm);
void	start_war(t_vm *vm);
void	start_war_vs(t_vm *vm);

void	print_players(t_player player[4], int nb_players);
void	print_result(t_vm *vm);
void	print_error(char *msg);

void	free_exit(t_vm *vm);
void	kill_process(t_vm *vm, t_process **process);

void	set_op_code(t_process *prc, t_vm *vm);

void	logical_op(t_process *prc, t_op_component *cmp);
void	fork_op(t_process *prc, t_op_component *cmp, t_vm *vm);
void	mem_op(t_process *prc, t_op_component *cmp);
int		live(t_vm *vm, t_process *prc);

void	set_carry(t_process *prc, t_op_component *cmp);
int		get_op_size(t_vm *vm, t_process *prc);

_Bool	parse_operation(t_vm *vm, t_process *prc);

int		get_mem(unsigned char *mem, int addr, int oct);
void	set_mem(unsigned char *mem, int addr, int val, int oct);
void	dump_arena(unsigned char *memory, int size);

WINDOW	*init_vis();
void	vm_vis(t_vm *vm, int fun, WINDOW *scr);
void	vis_state(char vis_state);
void	init_update_panel(t_vm *vm);
void	update_life_bars(t_vm *vm, int jumper);
void	update_state(int jumper, t_vm *vm);
void	detail_panel(t_vm *vm);
void	up_down_volume(int *vis_speed, int in);
void	max_min_speed(int *vis_speed);
void	init_speed_bars(int *vis_speed);
void	increase_speed(int *vis_speed);
void	decrease_speed(int *vis_speed);
int		clear_volume(void);
void	apply_update_pause(t_vm *vm, WINDOW *scr, int in);
WINDOW	*init_vis(void);
void	apply_update_pause(t_vm *vm, WINDOW *scr, int in);
void	init_players_vs(t_vm *vm, int **size);
void	put_color_players(t_vm *vm, int **size, int jumper, int *xopper);
void	help_panel(void);
void	line(t_vm *vm);
int		**players_exe_borders(t_player *players, int players_nbr);

#endif
