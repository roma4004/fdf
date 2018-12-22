# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/12/22 16:19:38 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc -O3 -Wall -Wextra -Werror

LIBKEY = -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

SRC_N =	main.c \
		draw.c \
		keys.c \
		init.c \
		hooks.c \
		color.c \
		parser.c \
		rotate.c \
		ram_man.c \
		effects.c \
		interface.c \
		service_func.c \
		get_next_line.c

SRC = $(addprefix src/, $(SRC_N))

OBJ = $(SRC:.c=.o)

LIBS = libraries/libft/libft.a

INC = -I libraries/libft/ -I Includes/

all: $(NAME)

%.o : %.c
	$(CC) $(INC) -c $< -o $@

$(NAME): liball $(OBJ)
	$(CC) $(LIBKEY) $(OBJ) $(INC) $(LIBS) -o $(NAME)

clean: libclean
	rm -f $(OBJ)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

liball:
	@make -C libraries/libft/ all

libclean:
	@make -C libraries/libft/ clean

libfclean:
	@make -C libraries/libft/ fclean

libre:
	@make -C libraries/libft/ re
