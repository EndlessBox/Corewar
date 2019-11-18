# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 14:40:46 by nouhaddo          #+#    #+#              #
#    Updated: 2019/11/13 04:24:51 by ybouladh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC =	main.c\
		read_content_flag.c\
		get_players_infos.c\
		arena.c\
		monitor.c\
		process.c\
		debugging.c\
		queue.c\
		op.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

LIBFT = ./libft

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(OBJ)  $(LIBFT)/libft.a -o $(NAME)

$(OBJ): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all
