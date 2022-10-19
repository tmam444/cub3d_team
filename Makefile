# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youskim <youskim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 19:41:21 by chulee            #+#    #+#              #
#    Updated: 2022/10/19 14:35:27 by youskim          ###   ########.fr        #
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
	 srcs/ft_calc.c \
	 srcs/ft_util.c \
	 srcs/ft_render.c \
	 srcs/ft_dda.c \
	 srcs/ft_parsing1.c \
	 srcs/ft_parsing2.c \
	 srcs/ft_parsing3.c \
	 srcs/ft_parsing_util.c \
	 srcs/ft_minimap.c
OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))
SRCS_B=bonus/main_bonus.c \
	 bonus/ft_atoi_bonus.c \
	 bonus/ft_parsing_bonus.c \
	 bonus/ft_split_bonus.c \
	 bonus/ft_strdup_bonus.c \
	 bonus/ft_strcmp_bonus.c \
	 bonus/ft_strlen_bonus.c \
	 bonus/get_next_line_bonus.c \
	 bonus/get_next_line_utils_bonus.c \
	 bonus/ft_memset_bonus.c \
	 bonus/ft_strjoin_bonus.c \
	 bonus/ft_isdigit_bonus.c \
	 bonus/ft_strchr_bonus.c \
	 bonus/ft_event_bonus.c \
	 bonus/ft_image_bonus.c \
	 bonus/ft_math_bonus.c \
	 bonus/ft_calc_bonus.c \
	 bonus/ft_util_bonus.c \
	 bonus/ft_render_bonus.c \
	 bonus/ft_dda_bonus.c \
	 bonus/ft_parsing1_bonus.c \
	 bonus/ft_parsing2_bonus.c \
	 bonus/ft_parsing3_bonus.c \
	 bonus/ft_parsing_util_bonus.c \
	 bonus/ft_minimap_bonus.c
OBJS_B = $(addprefix objs/, $(notdir $(SRCS_B:.c=.o)))
HEADERS = includes/cub3d.h
HEADERS_B = includes/cub3d_bonus.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_LIB = ./minilibx_opengl_20191021
MLX_FLAGS = -lm -L$(MLX_LIB) -lmlx -framework OpenGL -framework AppKit

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS_B)
	HEADERS_FILES = $(HEADERS_B)
else
	OBJ_FILES = $(OBJS)
	HEADERS_FILES = $(HEADERS)
endif

$(NAME) : $(OBJ_FILES)
		$(MAKE) -C $(MLX_LIB)
		$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJ_FILES)

$(B_NAME) : $(OBJ_FILES)
		$(MAKE) -C $(MLX_LIB)
		$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(B_NAME) $(OBJ_FILES)

objs/%.o : srcs/%.c $(HEADERS_FILES)
		$(CC) $(CFLAGS) -c $< -o $@

objs/%.o : bonus/%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		$(MAKE) -C $(MLX_LIB) clean
		rm -f $(OBJS) $(OBJS_B)

fclean : clean
		rm -f $(NAME) $(B_NAME)

bonus : 
		make WITH_BONUS=1 $(B_NAME)

all : $(NAME)

re : fclean all

.PHONY: clean fclean all re bonus

