# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 15:53:12 by souarrak          #+#    #+#              #
#    Updated: 2020/01/03 23:25:42 by nouhaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = corewar

ASM = asm

LIB_FT = libft/libft.a

VM_SRC = 	vm/main_vm.c\
			vm/get_input.c\
			vm/war.c\
			vm/init.c\
			vm/free_exit.c\
			vm/memory.c\
			vm/parse_operation.c\
			vm/helper.c\
			vm/operations.c\
			vm/visualizer/vis_00.c\
			vm/visualizer/panel.c\
			vm/visualizer/panel2.c\
			vm/visualizer/speed.c\
			vm/visualizer/speed2.c\
			vm/visualizer/color_init_pause.c

ASM_SRC =	asm_compiler/asm.c\
			asm_compiler/bytecode.c\
			asm_compiler/tools.c\
			asm_compiler/read_instruction.c\
			asm_compiler/op.c


ASM_OBJ = $(ASM_SRC:%c=%o)

VM_OBJ = $(VM_SRC:%c=%o)

VM_INCLUDE = -I vm/includes

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all : $(VM) $(ASM)

$(LIB_FT) :
	make re -C libft

$(VM) : $(VM_OBJ) $(addprefix vm/includes/,vm.h define.h op.h struct.h)
	make -C libft
	$(CC)  -lncurses $(CFLAGS) $(LIB_FT) $(VM_OBJ) -o $(VM)

$(ASM) : $(ASM_OBJ) asm_compiler/op.h asm_compiler/asm.h
	make -C libft
	$(CC) $(CFLAGS) $(LIB_FT)  $(ASM_OBJ) -o $(ASM)

clean :
	make clean -C libft
	/bin/rm -rf $(VM_OBJ) $(ASM_OBJ)

fclean : clean
	make fclean -C libft
	/bin/rm -rf $(VM) $(ASM)

re : fclean all
