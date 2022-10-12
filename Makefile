# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 19:41:21 by chulee            #+#    #+#              #
#    Updated: 2022/10/12 20:05:53 by chulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D
B_NAME=cub3D_bonus
SRCS=srcs/main.c
OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))
SRCS_B=bonus/main_bonus.c
OBJS_B = $(addprefix objs/, $(notdir $(SRCS_B:.c=.o)))
CC = cc
CFLAGS = -fsanitize=address -g
MLX_LIB = ./minilibx_opengl_20191021
MLX_FLAGS = -lm -L$(MLX_LIB) -lmlx -framework OpenGL -framework AppKit

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS_B)
else
	OBJ_FILES = $(OBJS)
endif

$(NAME) : $(OBJ_FILES)
		$(MAKE) -C $(MLX_LIB)
		$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJ_FILES)

$(B_NAME) : $(OBJ_FILES)
		$(MAKE) -C $(MLX_LIB)
		$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(B_NAME) $(OBJ_FILES)

objs/%.o : srcs/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		$(MAKE) -C $(MLX_LIB) clean
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

bonus : 
		make WITH_BONUS=1 $(B_NAME)

all : $(NAME)

re : fclean all

.PHONY: clean fclean all re bonus

