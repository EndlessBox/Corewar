/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:54:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/24 05:52:27 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BETWEEN(v, cmp1, cmp2) ((v) >= cmp1 && (v) <= cmp2)
# define ADDR(v) ((MEM_SIZE + (v)) % MEM_SIZE)

# define HEADER_SIZE PROG_NAME_LENGTH + COMMENT_LENGTH + 16
# define SIZE_TOTAL HEADER_SIZE + CHAMP_MAX_SIZE
# define MAX_DUMP 64
# define NEGATIVE_CONST 32768
# define PLAYER_CONST 4294967294
# define USAGE "./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."

#endif
