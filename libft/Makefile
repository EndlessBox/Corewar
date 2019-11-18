# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 15:42:01 by nouhaddo          #+#    #+#              #
#    Updated: 2019/11/11 13:41:31 by ybouladh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_abs.c\
	  ft_atoi.c\
	  ft_base_to_dec.c\
	  ft_binpow.c\
	  ft_bits_extend.c\
	  ft_bzero.c\
	  ft_error.c\
	  ft_find_t_str.c\
	  ft_findchar.c\
	  ft_free_t_link.c\
	  ft_free_t_str.c\
	  ft_get_file_content.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_itoa.c\
	  ft_listrevers.c\
	  ft_lputnstr.c\
	  ft_lputstr.c\
	  ft_lstadd.c\
	  ft_lstconcate.c\
	  ft_lstcount.c\
	  ft_lstdel.c\
	  ft_lstdelone.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstnew.c\
	  ft_manage_flag.c\
	  ft_manage_nbr.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_new_t_link.c\
	  ft_new_t_str.c\
	  ft_pow.c\
	  ft_print_res.c\
	  ft_print_t_str.c\
	  ft_printf.c\
	  ft_push_t_link.c\
	  ft_put_ntime.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_putwchar.c\
	  ft_putwstr.c\
	  ft_read_memory.c\
	  ft_realloc.c\
	  ft_removelist.c\
	  ft_searchlist.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strlowercase.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strnchr.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strndup.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strrev.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_strwlen.c\
	  ft_t_addr.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  print_characters.c\
	  print_float.c\
	  string_operations.c

OBJ = $(SRC:.c=.o)
	FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
