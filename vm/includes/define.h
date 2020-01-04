/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:54:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/27 22:50:19 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define ADDR(v) ((MEM_SIZE + (v)) % MEM_SIZE)

# define HEADER_SIZE PROG_NAME_LENGTH + COMMENT_LENGTH + 16
# define SIZE_TOTAL HEADER_SIZE + CHAMP_MAX_SIZE
# define MAX_DUMP 64
# define NEGATIVE_CONST 32768
# define PLAYER_CONST 4294967294
# define USAGE "./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."
# define VIS_TYPE "%2s"
# define SCALE_H  3
# define SCALE_J  2
# define BORDER_TOP 5
# define LEFT_BORDER 110
# define SEPARATOR_TOP 35
# define COUNT_DOWN_J ((32 - 10 * SCALE_J) / 2) * SCALE_J + BORDER_TOP
# define COUNT_DOWN_H ((128  - 6 * SCALE_H) * SCALE_J / 2) + LEFT_BORDER
# define COUNT_DOWN_H_E ((128  - 30 * SCALE_H) * SCALE_J / 2) + LEFT_BORDER
# define SPEED 5000
# define MAX_SPEED 100000

#endif
