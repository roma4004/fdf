# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/07/17 15:41:44 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc -Wall -Wextra -Werror

LIBKEY = -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

SRC_N =	main.c \
		draw.c \
		keys.c \
		init.c \
		hooks.c \
		color.c \
		debug.c \
		parser.c \
		rotate.c \
		for_lib.c \
		ram_man.c \
		effects.c \
		service_func.c \
		get_next_line.c \
		experimental_code.c \

SRC = $(addprefix src/, $(SRC_N))

OBJ = $(SRC:.c=.o)

LIBS = libft/libft.a

build: 
	gcc -Wall -Wextra -Werror -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit src/main.c src/get_next_line.c

all: $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME): liball $(OBJ)
	$(CC) $(LIBKEY) $(OBJ) $(LIBS) -o $(NAME) 

clean: libclean
	rm -f $(OBJ)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

liball:
	@make -C libft/ all

libclean:
	@make -C libft/ clean

libfclean:
	@make -C libft/ fclean

libre:
	@make -C libft/ re
