# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2019/03/15 16:53:41 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc -O3 -Wall -Wextra -Werror

LIBKEY = -L ./libraries/minilibx -lmlx \
		 -framework OpenGL \
		 -framework AppKit

PROJ_OBJ_PATH = objectives
PROJ_SRC_PATH = sources

INC = -I ./libraries/minilibx -I libraries/libft/ -I includes/

SRC_N = main.c \
		draw.c \
		keys.c \
		parser.c \
		rotate.c \
		effects.c \
		get_next_line.c

SRC = $(addprefix $(PROJ_SRC_PATH)/, $(SRC_N))

OBJ = $(addprefix ./$(PROJ_OBJ_PATH)/, $(SRC_N:.c=.o))

LIBS = libraries/libft/libft.a

all: $(NAME)

./$(PROJ_OBJ_PATH)/%.o : ./$(PROJ_SRC_PATH)/%.c
	$(CC) $(INC) -c $< -o $@

$(NAME): objdir liball $(OBJ)
	$(CC) $(LIBKEY) $(OBJ) $(INC) $(LIBS) -o $(NAME)

objdir:
	mkdir -p $(PROJ_OBJ_PATH)

clean: libclean
	rm -rf $(PROJ_OBJ_PATH)

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
