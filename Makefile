# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youskim <youskim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 19:41:21 by chulee            #+#    #+#              #
#    Updated: 2022/10/18 15:04:34 by youskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D
B_NAME=cub3D_bonus
SRCS=srcs/main.c \
	 srcs/ft_atoi.c \
	 srcs/ft_parsing.c \
	 srcs/ft_split.c \
	 srcs/ft_strdup.c \
	 srcs/ft_strcmp.c \
	 srcs/ft_strlen.c \
	 srcs/get_next_line.c \
	 srcs/get_next_line_utils.c \
	 srcs/ft_memset.c \
	 srcs/ft_strjoin.c \
	 srcs/ft_isdigit.c \
	 srcs/ft_strchr.c \
	 srcs/ft_event.c \
	 srcs/ft_image.c \
	 srcs/ft_math.c \
	 srcs/ft_util.c \
	 srcs/ft_render.c \
	 srcs/ft_dda.c

OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))
SRCS_B=bonus/main_bonus.c
OBJS_B = $(addprefix objs/, $(notdir $(SRCS_B:.c=.o)))
CC = cc
CFLAGS =
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

