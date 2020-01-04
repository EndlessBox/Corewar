/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 21:35:05 by ybouladh          #+#    #+#             */
/*   Updated: 2020/01/04 01:24:33 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	color_proc(t_arena arena, t_process *tmp_procs, int tmp_pc)
{
	int jumper;

	if (tmp_procs->cycle == 0)
	{
		attron(COLOR_PAIR(9));
		mvprintw(((tmp_pc / 128) * SCALE_J + BORDER_TOP), (tmp_pc % 128) *
		SCALE_H + ((COLS - 128 * SCALE_H) / 2), "%02x", arena.memory[tmp_pc]);
		attroff(COLOR_PAIR(9));
	}
	else if (tmp_procs->cycle == 1)
	{
		jumper = -1;
		attron(COLOR_PAIR(-tmp_procs->id_player + 4) | A_BOLD);
		while (++jumper < tmp_procs->cmp.step)
			mvprintw((((((tmp_pc + jumper)) / 128) % 32) * SCALE_J +
			BORDER_TOP), ((tmp_pc + jumper) % 128) * SCALE_H +
			((COLS - 128 * SCALE_H) / 2),
			"%02x", arena.memory[tmp_pc + jumper]);
		attroff(COLOR_PAIR(-tmp_procs->id_player + 4) | A_BOLD);
	}
}

void	norm_vis(t_vm *vm)
{
	t_process		*tmp_procs;
	unsigned char	*arena;
	int				tmp_pc;

	tmp_procs = vm->arena.process;
	arena = vm->arena.memory;
	tmp_pc = 0;
	while (tmp_procs)
	{
		tmp_pc = tmp_procs->pc % MEM_SIZE;
		color_proc(vm->arena, tmp_procs, tmp_pc);
		tmp_procs = tmp_procs->next;
		refresh();
	}
}

void	update_state_vis_pnl(t_vm *vm)
{
	vis_state(vm->visu_event);
	norm_vis(vm);
	line(vm);
	init_update_panel(vm);
}

void	initialize_ply_pnl_vlm(t_vm *vm, int **size)
{
	clear();
	init_players_vs(vm, size);
	detail_panel(vm);
	up_down_volume(&vm->visu_spd, -1);
	help_panel();
}

void	vm_vis(t_vm *vm, int fun, WINDOW *scr)
{
	int		**size;
	int		in;

	size = players_exe_borders(vm->player, vm->nb_players);
	if (fun == 0)
		initialize_ply_pnl_vlm(vm, size);
	else if (fun == 1)
		update_state_vis_pnl(vm);
	else if (fun == -1)
	{
		free(size[0]);
		free(size[1]);
		free(size);
		nodelay(scr, FALSE);
	}
	in = getch();
	if (in != ERR && (in == '+' || in == '-') && vm->visu_event != 'p')
		up_down_volume(&vm->visu_spd, in);
	else if (in != ERR && in == 'p')
		apply_update_pause(vm, scr, in);
	refresh();
	usleep(vm->visu_spd);
}
