/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:44:58 by chulee            #+#    #+#             */
/*   Updated: 2022/10/07 19:33:07 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "mlx.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define MAP_SIZE 50
# define MAP_BUFFER 25
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_EXIT 17
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_location {
	int	x;
	int	y;
}	t_location;

typedef struct s_img {
	void	*img_ptr;
	int		width;
	int		height;
}	t_img;

typedef struct s_map {
	char	**map;
	char	*err_msg;
	int		start_count;
	int		end_count;
	int		item_count;
	int		height;
	int		width;
}	t_map;

typedef struct s_win {
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map_info;
	t_img		tile;
	t_img		wall;
	t_img		item;
	t_img		door;
	t_img		player;
	t_img		bomb;
	t_location	player_xy;
	int			life;
	int			move_count;
	int			sprite_num;
}	t_win;

char	*ft_strchr(const char *s, int c);
void	ft_clear(t_win *mlx_vars);
int		ft_strlen(char *str);
void	ft_error(char *str);
void	ft_reset_mlx_vars(t_win *mlx_vars);
void	ft_check_map_first_line(char *temp, t_map *map_info);
void	ft_check_middle_line_format(char *str, t_map *map_info);
void	ft_check_map_last_line(char *line, t_map *map_info);
void	ft_check_all_line(int fd, t_map *map_info);
void	ft_check_map_format(char *filename, t_win *mlx_vars);
char	*ft_itoa(int n);
char	*ft_strjoin(char *str1, char *str2);
int		ft_game_exit(t_win *mlx_vars);
void	ft_fill_tile(t_win *mlx_vars);
void	ft_print_map_image(t_win *mlx_vars, int x, int y);
void	ft_print_map(t_win *mlx_vars);
int		ft_render(t_win *mlx_vars);
void	ft_reset_mlx_vars(t_win *mlx_vars);
void	ft_move(t_win *mlx_vars, int keycode);
int		ft_control_press_key(int keycode, t_win *mlx_vars);
void	ft_init_game(t_win *mlx_vars);
void	ft_malloc_map(char *filename, t_win *mlx_vars);

#endif
