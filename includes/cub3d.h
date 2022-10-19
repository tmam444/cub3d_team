/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:44:58 by chulee            #+#    #+#             */
/*   Updated: 2022/10/19 14:51:45 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../minilibx_opengl_20191021/mlx.h"

# define EPS				(1e-6)
# define KEY_LEFT			123
# define KEY_RIGHT			124
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_ESC			53
# define X_EVENT_KEY_PRESS	2
# define IMG_SIZE 			4
# define TYPE_LENGTH 		6
# define TRUE        		1
# define FALSE      		0
# define SX					1280
# define SY					960
# define FOV				60
# define ROT_UNIT			0.1
# define MOVE_UNIT			0.2

enum e_hit_dir {
	VERT,
	HORIZ
};

typedef enum e_dir {
	DIR_N=0,
	DIR_E,
	DIR_W,
	DIR_S
}	t_dir;

typedef struct s_player
{
	double	x;
	double	y;
	double	th;
}	t_player;

typedef struct s_img
{
	void			*img;
	unsigned int	*data;
	int				bpp;
	int				line_size;
	int				endian;
	int				w;
	int				h;
}	t_img;

typedef struct s_info
{
	int			**map;
	int			map_w;
	int			map_h;
	char		*path[IMG_SIZE];
	int			floor_color;
	int			ceilling_color;
}	t_info;

typedef struct s_DDA
{
	int		xstep;
	int		ystep;
	double	fx;
	double	gy;
	double	nx;
	double	ny;
	double	dist_vert;
	double	dist_horiz;
	int		hit_dir;
	int		map_x;
	int		map_y;
	double	wx;
	double	wy;
}	t_DDA;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_info		info;
	t_img		background;
	t_img		imgs[IMG_SIZE];
	t_DDA		dda;
}				t_mlx;

// parsing
void	ft_parsing(t_mlx *info, char *file);
void	ft_check_type(t_mlx *mlx, char *line);
void	ft_setting_player(t_mlx *mlx, int x, int y, char th);
void	ft_save_map(t_mlx *mlx, char **split);
void	ft_map_size_check(t_mlx *mlx, char **split);
void	ft_rotate_map(t_mlx *mlx);
void	ft_check_empty_line(char **split);
void	ft_check_map_surround_wall(t_mlx *mlx);
void	ft_check_validate(t_mlx *mlx);
void	ft_rotate_player(t_mlx *mlx, int **new_map);

//utils
char	**ft_split(char const *s, char c);
void	ft_split_clear(char **split);
int		ft_assert(int check, const char *err_msg);
char	*ft_strdup(const char *str);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);
void	ft_clear(t_mlx *mlx);
int		map_validate_check(int x, int y, t_mlx *mlx);
void	ft_split_clear(char **split);
void	ft_clear_mlx(t_mlx *mlx);

// event
int		ft_player_rotate(int keycode, t_player *player);
int		ft_move_wasd(int keycode, t_player *player);
int		ft_player_move(int keycode, t_mlx *mlx);
int		ft_key_event(int keycode, t_mlx *mlx);
int		ft_program_exit(t_mlx *mlx);

// image
void	ft_load_image(t_mlx *mlx);
void	pixel_put(t_mlx *mlx, int x, int y, int color);
void	make_bg(t_mlx *mlx);

// math
double	ft_deg_to_rad(double d);
double	ft_min(double a, double b);
double	ft_max(double a, double b);

// calc
int		check_zero(double d);
double	ray_dist(double player_x, double player_y, double x, double y);

// render
int		ft_render(t_mlx *mlx);
void	ft_render_minimap(t_mlx *mlx);

// ray casting
double	cast_single_ray(int x, t_dir *wdir, t_mlx *mlx);
void	calc_bump_wall(double ray, t_dir *wdir, t_mlx *mlx);

#endif
