/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:48 by chulee            #+#    #+#             */
/*   Updated: 2022/10/17 19:20:07 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

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

int map_get_cell( int x, int y, t_mlx *mlx)
{
	if (x >= 0 && x < mlx->info.map_h && y >= 0 && y < mlx->info.map_w)
		return (mlx->info.map[x][y]);
	else
		return (-1);
}

int get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy, t_mlx *mlx)
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    double f=INFINITY, g=INFINITY;
    int hit = false;
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
        int cell = map_get_cell(mapx, mapy, mlx);
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

double cast_single_ray( int x, t_player *player, dir_t *wdir, t_mlx *mlx)
{
    double ray = (player->th + FOVH_2) - (x * ANGLE_PER_PIXEL);

    if( get_wall_intersection(ray, player->x, player->y, wdir, &player->wx, &player->wy, mlx) == false )
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

int	ft_player_move(int keycode, t_mlx *mlx)
{
	t_player	temp;

	temp.x = mlx->player.x;
	temp.y = mlx->player.y;
	temp.th = mlx->player.th;
	ft_player_rotate(keycode, &mlx->player);
	ft_move_wasd(keycode, &temp);
	if (map_get_cell(temp.x, temp.y, mlx) == 0)
	{
		mlx->player.x = temp.x;
		mlx->player.y = temp.y;
	}
	return (0);
}

void	ft_clear(t_mlx *mlx)
{
	int	i;

	if (mlx->info.map)
	{
		i = 0;
		while (i < mlx->info.map_h)
		{
			if (mlx->info.map[i])
				free(mlx->info.map[i]);
			i++;
		}
		free(mlx->info.map);
	}
}

int	ft_key_event(int keycode, t_mlx *mlx)
{
	int	i;

	if (keycode == KEY_ESC)
	{
		ft_clear(mlx);
		exit(0);
	}
	else
		ft_player_move(keycode, mlx);
	return (0);
}

int	ft_assert(int check, const char *err_msg)
{
	if (!check)
	{
		write(2, "Error\n", 6);
		write(2, err_msg, strlen(err_msg));
		write(2, "\n", 1);
		exit(1);
	}
	return (1);
}

int	ft_render(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->background.img, 0, 0);
    for( int x=0; x<SX; x++ ) {
		dir_t	wdir;
        double	wdist = cast_single_ray(x, &mlx->player, &wdir, mlx);
		draw_wall(mlx, wdist, x, wdir);
    }
	return (0);
}

void	ft_load_image(t_mlx *mlx)
{
	int	i;
	
	mlx->imgs[DIR_N].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->info.path[DIR_N], &mlx->imgs[DIR_N].w, &mlx->imgs[DIR_N].h);
	mlx->imgs[DIR_S].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->info.path[DIR_S], &mlx->imgs[DIR_S].w, &mlx->imgs[DIR_S].h);
	mlx->imgs[DIR_W].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->info.path[DIR_W], &mlx->imgs[DIR_W].w, &mlx->imgs[DIR_W].h);
	mlx->imgs[DIR_E].img = \
			mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->info.path[DIR_E], &mlx->imgs[DIR_E].w, &mlx->imgs[DIR_E].h);
	i = -1;
	while (++i < 4)
		ft_assert(mlx->imgs[i].img != NULL, "image Load Error!");
	mlx->imgs[DIR_N].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_N].img, \
					&mlx->imgs[DIR_N].bpp, &mlx->imgs[DIR_N].line_size, &mlx->imgs[DIR_N].endian);
	mlx->imgs[DIR_S].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_S].img, \
					&mlx->imgs[DIR_S].bpp, &mlx->imgs[DIR_S].line_size, &mlx->imgs[DIR_S].endian);
	mlx->imgs[DIR_W].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_W].img, \
					&mlx->imgs[DIR_W].bpp, &mlx->imgs[DIR_W].line_size, &mlx->imgs[DIR_W].endian);
	mlx->imgs[DIR_E].data = (unsigned int *)mlx_get_data_addr(mlx->imgs[DIR_E].img, \
					&mlx->imgs[DIR_E].bpp, &mlx->imgs[DIR_E].line_size, &mlx->imgs[DIR_E].endian);
}

void    bg_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char *dst;

    dst = (char*)mlx->background.data + (y * mlx->background.line_size + x * (mlx->background.bpp / 8));
	*(unsigned int*)dst = color;
}

void	make_bg(t_mlx *mlx)
{
	mlx->background.img = mlx_new_image(mlx->mlx_ptr, SX, SY);
	mlx->background.data = (unsigned int *)mlx_get_data_addr(mlx->background.img, &mlx->background.bpp, \
					&mlx->background.line_size, &mlx->background.endian);
	for (int x = 0; x < SX; x++)
	{
		for (int y = 0; y < SY; y++)
		{
			if (y / (SY / 2) == 0)
				bg_pixel_put(mlx, x, y, mlx->info.ceilling_color);
			else
				bg_pixel_put(mlx, x, y, mlx->info.floor_color);
		}
	}
}

void	ft_init(t_mlx *mlx)
{
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->info.floor_color = -1;
	mlx->info.ceilling_color = -1;
	mlx->player.x = -1;
	mlx->player.y = -1;
	mlx->player.th = -1;
}

void	ft_file_type_check(char *filename)
{
	static const char	*file_type = ".cub";
	int					i;
	int					len;

	len = ft_strlen(filename);
	i = ft_strlen(file_type);
	ft_assert(len > i, "File Type Error");
	while (i > 0)
		ft_assert(filename[--len] == file_type[--i], "File Type Error");
}

int main(int ac, char** av)
{
	t_mlx		mlx;

	ft_assert(ac == 2, "please input only map file");
	ft_file_type_check(av[1]);
	ft_init(&mlx);
	ft_parsing(&mlx, av[1]);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, SX, SY, "A simple example");
	ft_load_image(&mlx);
	make_bg(&mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, \
			ft_player_move, &mlx);
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
