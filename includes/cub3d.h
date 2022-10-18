/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:44:58 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 15:04:14 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <float.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../minilibx_opengl_20191021/mlx.h"

#define  Floor 0xFFFFFF
#define  Ceiling 0x000000

#define  EPS            (1e-6)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))
#define  KEY_LEFT	123
#define  KEY_RIGHT	124
#define  KEY_W 13
#define  KEY_A 0
#define  KEY_S 1
#define	 KEY_D 2
#define  KEY_ESC 53
#define	 X_EVENT_KEY_PRESS 2
#define  IMG_SIZE 4
#define  TYPE_LENGTH 6
#define  true        1
#define  false       0

#define  SX         1280    /* screen width */
#define  SY         1024     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0
#define  ROT_UNIT   0.05
#define  MOVE_UNIT  0.2
#define  _2PI       2 * M_PI /* 2 * M_PI */

enum { VERT, HORIZ };

typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

// #define  MAPX   6
// #define  MAPY   5

typedef struct	s_player
{
	double	x;
	double	wx;
	double	y;
	double	wy;
	double	th;
}				t_player;

typedef struct s_img
{
	void			*img;
	unsigned int	*data;
	int				bpp;
	int				line_size;
	int				endian;
	int				w;
	int				h;
}			t_img;

typedef struct s_info
{
	int			**map;
	int			map_w;
	int			map_h;
	char		*path[IMG_SIZE];
	int			floor_color;
	int			ceilling_color;
}			t_info;

typedef struct	s_DDA
{
	int	xstep;
	int	ystep;

	double	fx;
	double	gy;

	double	nx;
	double	ny;

	double	dist_vert;
	double	dist_horiz;

	int		hit_dir;
	bool 	hit;

	int	map_x;
	int	map_y;
}		t_DDA;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_player	player;
	t_info		info;
	t_img		background;
	t_img		imgs[IMG_SIZE];
	t_DDA		DDA;
}				t_mlx;

void	ft_parsing(t_mlx *info, char *file);

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
int 	map_validate_check( int x, int y, t_mlx *mlx);

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
int		check_zero(double d);
double	ray_dist(double player_x, double player_y, double x, double y);

// render
int		ft_render(t_mlx *mlx);

// ray casting
int		get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy, t_mlx *mlx);
double	cast_single_ray( int x, t_player *player, dir_t *wdir, t_mlx *mlx);


#endif
