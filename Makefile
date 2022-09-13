# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 14:45:57 by ygbouri           #+#    #+#              #
#    Updated: 2022/09/13 16:31:10 by ygbouri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = cub.c src/parsing/check_clr.c src/parsing/check_map.c src/parsing/pars_line.c\
		src/parsing/split.c src/parsing/utils.c src/parsing/utils1.c\
		src/parsing/utils2.c src/gamedis/gameutils.c

OBJ = $(SRC:.c=.o)

CC = @gcc

NAME = cub3D

MLX = -framework OpenGL -framework Appkit

CFLAGS = -Wall -Wextra -Werror

HEADER = cub3d.h

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx $(MLX) -o $(NAME) -g
	@echo "mandatory is done"

clean :
	@rm -rf $(OBJ)
	@echo "clean"

fclean : clean
	@rm -rf $(NAME)

re : fclean all
