# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 14:45:57 by ygbouri           #+#    #+#              #
#    Updated: 2022/10/09 15:22:28 by momayaz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = cub.c src/parsing/check_clr.c src/parsing/check_map.c src/parsing/pars_line.c\
		src/parsing/split.c src/parsing/utils.c src/parsing/utils1.c\
		src/parsing/utils2.c src/gamedis/gameutils.c src/gamedis/gameutils1.c\
		src/gamedis/gameutils2.c src/gamedis/gameutils3.c src/gamedis/gameutils4.c\
		src/gamedis/gameutils5.c src/gamedis/gameutils6.c src/gamedis/gameutils7.c\
		src/gamedis/gameutils8.c src/gamedis/gameutils9.c

OBJ = $(SRC:.c=.o)

CC = @gcc

NAME = cub3D

MLX = -framework OpenGL -framework Appkit

CFLAGS = -Wall -Wextra 

HEADER = cub3d.h

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@$(CC)  $(SRC) -lmlx $(MLX) -o $(NAME) -g
	@echo "mandatory is done"

bonus : $(OBJ) $(HEADER)
	@$(CC)  $(SRC) -lmlx $(MLX) -o $(NAME) -g
	@echo "bonus is done"

clean :
	@rm -rf $(OBJ)
	@echo "clean"

fclean : clean
	@rm -rf $(NAME)

re : fclean all
