/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:48 by chulee            #+#    #+#             */
/*   Updated: 2022/10/12 22:22:54 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
    {1,1,1,1,1}, /* [0][*] */
    {1,0,0,0,1}, /* [1][*] */
    {1,0,0,0,1}, /* [2][*] */
    {1,1,0,0,1}, /* and so on... */
    {1,1,0,0,1},
    {1,1,1,1,1}
};



int sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

int	real_x(int x, int y)
{
	return (y);
}

int	real_y(int x, int y)
{
	int ret;

	ret = x - MAPX;
	if (ret < 0)
		return (ret * -1);
	else
		return (ret);
}

int map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

bool get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    double f=INFINITY, g=INFINITY;
    bool hit = false;
    int hit_side; /* either VERT or HORIZ */

    while( !hit )
    {
        int mapx, mapy;

        if( xstep != 0 ) f = xslope * (nx-px) + py;
        if( ystep != 0 ) g = yslope * (ny-py) + px;

        /* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
        double dist_v = l2dist(px, py, nx, f);
        double dist_h = l2dist(px, py, g, ny);

        if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
            mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
            mapy = (int) f;
            hit_side = VERT;
        }
        else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
        }
        int cell = map_get_cell(mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_E : DIR_W;
                *wx = nx;
                *wy = f;
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_N : DIR_S;
                *wx = g;
                *wy = ny;
            }
            hit = true;
            break;
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

double cast_single_ray( int x, t_player *player, dir_t *wdir )
{
    double ray = (player->th + FOVH_2) - (x * ANGLE_PER_PIXEL);

    if( get_wall_intersection(ray, player->x, player->y, wdir, &player->wx, &player->wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(player->x, player->y, player->wx, player->wy);
	wdist *= cos(player->th - ray);  /* 보정 */
    return wdist;
}

int get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

void draw_wall(t_mlx* gr, double wdist, int x, dir_t wdir)
{
    int wh = get_wall_height(wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((SY - wh)/2.0);
    int y1 = y0 + wh - 1;

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SY-1, y1);
	double txratio = (wdir == DIR_W || wdir == DIR_E) ? \
					 (gr->player.wy-floor(gr->player.wy)) : (gr->player.wx-floor(gr->player.wx));
    int tx = (int)(txratio * 64);
	for (int y = ystart; y < yend; y++)
	{
		int ty = (int)((double)(y-y0) * 64 / wh); /* texture row # */
		int color;
		if (wdir == DIR_W || wdir == DIR_N)
			color = gr->imgs[wdir].data[ty * 64 + tx];
		else
			color = gr->imgs[wdir].data[ty * 64 - tx];
		mlx_pixel_put(gr->mlx_ptr, gr->win, x, y, color);
	}
}

int	ft_player_rotate(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		player->th += 1 * ROT_UNIT;
	else if (keycode == KEY_RIGHT)
		player->th -= 1 * ROT_UNIT;
    if (player->th < 0)
		player->th += _2PI;
    else if (player->th > _2PI)
		player->th -= _2PI;
	return (0);
}

int	ft_move_wasd(int keycode, t_player *player)
{
	if (keycode == KEY_W)
	{
		player->x += MOVE_UNIT * cos(player->th);
		player->y += MOVE_UNIT * sin(player->th);
	}
	else if (keycode == KEY_S)
	{
		player->x -= MOVE_UNIT * cos(player->th);
		player->y -= MOVE_UNIT * sin(player->th);
	}
	else if (keycode == KEY_D)
	{
		player->x += MOVE_UNIT * cos(player->th - M_PI_2);
		player->y += MOVE_UNIT * sin(player->th - M_PI_2);
	}
	else if (keycode == KEY_A)
	{
		player->x += MOVE_UNIT * cos(player->th + M_PI_2);
		player->y += MOVE_UNIT * sin(player->th + M_PI_2);
	}
	return (0);
}

int	ft_player_move(int keycode, t_player *player)
{
	double	temp_x;
	double	temp_y;

	ft_player_rotate(keycode, player);
	temp_x = player->x;
	temp_y = player->y;
	ft_move_wasd(keycode, player);
	if (map_get_cell(player->x, player->y) == 1 || map_get_cell(player->x, player->y) == -1)
	{
		player->x = temp_x;
		player->y = temp_y;
	}
	return (0);
}

int	ft_key_event(int keycode, t_player *player)
{
	ft_player_rotate(keycode, player);
	ft_player_move(keycode, player);
	return (0);
}

void	ft_assert(int check, const char *err_msg)
{
	if (!check)
	{
		write(2, err_msg, strlen(err_msg));
		exit(1);
	}
}

int	ft_render(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->bg, 0, 0);
    for( int x=0; x<SX; x++ ) {
		dir_t	wdir;
        double	wdist = cast_single_ray(x, &mlx->player, &wdir);
		draw_wall(mlx, wdist, x, wdir);
    }
	return (0);
}

void	ft_load_image(t_mlx *mlx)
{
	mlx->imgs[DIR_N].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture/wall_n.xpm", &mlx->imgs[DIR_N].w, &mlx->imgs[DIR_N].h);
	mlx->imgs[DIR_N].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_N].img, \
					&mlx->imgs[DIR_N].bpp, &mlx->imgs[DIR_N].line_size, &mlx->imgs[DIR_N].endian);
	mlx->imgs[DIR_S].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture/wall_s.xpm", &mlx->imgs[DIR_S].w, &mlx->imgs[DIR_S].h);
	mlx->imgs[DIR_S].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_S].img, \
					&mlx->imgs[DIR_S].bpp, &mlx->imgs[DIR_S].line_size, &mlx->imgs[DIR_S].endian);
	mlx->imgs[DIR_W].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture/wall_w.xpm", &mlx->imgs[DIR_W].w, &mlx->imgs[DIR_W].h);
	mlx->imgs[DIR_W].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_W].img, \
					&mlx->imgs[DIR_W].bpp, &mlx->imgs[DIR_W].line_size, &mlx->imgs[DIR_W].endian);
	mlx->imgs[DIR_E].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture/wall_e.xpm", &mlx->imgs[DIR_E].w, &mlx->imgs[DIR_E].h);
	mlx->imgs[DIR_E].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_E].img, \
					&mlx->imgs[DIR_E].bpp, &mlx->imgs[DIR_E].line_size, &mlx->imgs[DIR_E].endian);
}

void    bg_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    dst = mlx->bg_addr + (y * mlx->bg_line_l + x * (mlx->bg_bbp / 8));
	*(unsigned int*)dst = color;
}

void	make_bg(t_mlx *mlx)
{
	mlx->bg = mlx_new_image(mlx->mlx_ptr, SX, SY);
	mlx->bg_addr = mlx_get_data_addr(mlx->bg, &mlx->bg_bbp, &mlx->bg_line_l, &mlx->bg_endian);
	for (int x = 0; x < SX; x++)
	{
		for (int y = 0; y < SY; y++)
		{
			if (y / (SY / 2) == 0)
				bg_pixel_put(mlx, x, y, Ceiling);
			else
				bg_pixel_put(mlx, x, y, Floor);
		}
	}
}

int main(int ac, char** av)
{
	t_mlx		mlx;

	ft_assert(ac == 4, "usage: ./cub3D x y th(deg)\n");
	

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, SX, SY, "A simple example");
    mlx.player.x = atof(av[1]);
    mlx.player.y = atof(av[2]);
    mlx.player.th = deg2rad(atof(av[3]));
	ft_load_image(&mlx);
	make_bg(&mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, \
			ft_player_move, &mlx.player);
	mlx_loop_hook(mlx.mlx_ptr, ft_render, &mlx);
	mlx_loop(mlx.mlx_ptr);
    return 0;
}

//맵이 동서남북이 제대로 출력이 안됨

// 오른쪽 = y, 아래쪽 = x
// {1,1,1,1,1}    # # # # # # 이렇게 나오는데, 왼쪽으로 90도 돌아간듯한 모습.. 우리가 원하는건
// {1,0,0,0,1} 	  # . . . . # 그대로 나와야 된다.
// {1,0,0,0,1}    # . . . . #
// {1,1,0,0,1}    # . . # # #
// {1,1,0,0,1}    # # # # # #
// {1,1,1,1,1}

// 오른쪽 = x, 위쪽 = y
// # # # # #   이렇게 그대로 찍혀야 우리가 원하는 맵 모습이 된다.
// # . . . #   왼쪽 맨 아래를 0,0 인 것 처럼 탐색해야..(player위치도 보정해야됨)
// # . . . #   좌표 얻어 올 때 -> map[y][|x - xlen|] 이렇게..?
// # # . . #   -->이거는 사각형일 경우에만 적용가능....? --> 어차피 플레이어는 벽 안에있을거고, 시야각 안에있는 좌표계산만 하면 되니까 상관없을듯
// # # . . #   --> ray계산할 때만 이런식으로 x, y 를 바꿔서 하면 될듯?
// # # # # #
