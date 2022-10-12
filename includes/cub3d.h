/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:44:58 by chulee            #+#    #+#             */
/*   Updated: 2022/10/12 20:06:28 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <float.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
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
#define	 X_EVENT_KEY_PRESS 2
#define  IMG_SIZE 4

#define  SX         400     /* screen width */
#define  SY         250     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0
#define  ROT_UNIT   0.03
#define  MOVE_UNIT  0.1
#define  _2PI       2 * M_PI /* 2 * M_PI */

enum { VERT, HORIZ };

typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

#define  MAPX   6
#define  MAPY   5

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
	char		*path[IMG_SIZE];
	int			floor_color;
	int			ceilling_color;
}			t_info;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	void		*bg;
	void		*bg_addr;
	int			bg_bbp;
	int			bg_line_l;
	int			bg_endian;
	t_player	player;
	t_info		info;
	t_img		background;
	t_img		imgs[IMG_SIZE];
}				t_mlx;



#endif
