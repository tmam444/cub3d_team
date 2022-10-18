#include "../includes/cub3d.h"

double	calc_txratio(t_mlx *mlx, dir_t wdir)
{
	if (wdir == DIR_W || wdir == DIR_E)
		return (mlx->player.wy - floor(mlx->player.wy));
	else
		return (mlx->player.wx - floor(mlx->player.wx));
}

int get_wall_height(double dist)
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

void	draw_wall(t_mlx *mlx, double wdist, int x, dir_t wdir)
{
	int	wall_height;
	int	y[2];
	int	y_start_end[2];
	int tx_ty[2];

	wall_height = get_wall_height(wdist);
	y[0] = (int)((SY - wall_height) / 2);
	y[1] = y[0] + wall_height - 1;
	y_start_end[0] = max(0, y[0]);
	y_start_end[1] = min(SY - 1, y[1]);
	tx_ty[0] = (int)(calc_txratio(mlx, wdir) * 64);
	while (y_start_end[0] < y_start_end[1])
	{
		tx_ty[1] = (int)((double)(y_start_end[0] - y[0]) * 64 / wall_height);
		if (wdir == DIR_W || wdir == DIR_N)
			bg_pixel_put(mlx, x, y, mlx->imgs[wdir].data[tx_ty[1] * 64 + tx_ty[0]]);
		else
			bg_pixel_put(mlx, x, y, mlx->imgs[wdir].data[tx_ty[1] * 64 - tx_ty[0]]);
		y_start_end[0] += 1;
	}
}

double	ray_dist(double player_x, double player_y, double x, double y)
{
	double	dx;
	double	dy;

	dx = player_x - x;
	dy = player_y - y;
	return (sqrt(dx*dx + dy*dy));
}

int	check_zero(double d)
{
	if (fabs(d) < EPS)
	{
		return (0);
	}
	else
	{
		if (d > 0)
			return (1);
		else
			return (-1);
	}	
}

void	get_fx_gy(double ray, t_player *player, t_DDA *DDA)
{
	DDA->fx = INFINITY;
	DDA->gy = INFINITY;

	if (DDA->xstep != 0)
		DDA->fx = tan(ray) * (DDA->nx - player->x) + player->y;
	if (DDA->ystep != 0)
		DDA->gy = (1 / tan(ray)) * (DDA->ny - player->y) + player->x;
}

void	get_nx_ny(t_player *player, t_DDA *DDA)
{
	if (DDA->xstep > 0)
		DDA->nx = floor(player->x) + 1;
	else if (DDA->xstep < 0)
		DDA->nx = ceil(player->x) - 1;
	else
		DDA->nx = player->x;

	if (DDA->ystep > 0)
		DDA->ny = floor(player->y) + 1;
	else if (DDA->ystep < 0)
		DDA->ny = ceil(player->y) - 1;
	else
		DDA->ny = player->y;
}

int	map_get_cell(int x, int y, t_info *info)
{
	if(x >= 0 && x < info->map_h && y >= 0 && y < info->map_w)
		return (info->map[x][y]);
	else
		return (-1);
}

int	get_map_type(t_DDA *DDA, t_info *info)
{
	if (DDA->dist_vert < DDA->dist_horiz)
	{
		if (DDA->xstep == 1)
			DDA->map_x = (int)DDA->nx;
		else
			DDA->map_x = (int)DDA->nx - 1;
		DDA->map_y = (int)DDA->fx;
		DDA->hit_dir = VERT;
	}
	else
	{
		if (DDA->ystep == 1)
			DDA->map_y = (int)DDA->ny;
		else
			DDA->map_y = (int)DDA->ny - 1;
		DDA->map_x = (int)DDA->gy;
		DDA->hit_dir = HORIZ;
	}
	return (map_get_cell(DDA->map_x, DDA->map_y, info));
}

int	check_map_type(t_player *player, t_DDA *DDA, int map_type, dir_t *wdir)
{
	if (map_type == 1)
	{
		if (DDA->hit_dir == VERT)
		{
			if (DDA->xstep > 0)
				*wdir = DIR_E;
			else
				*wdir = DIR_W;
			player->wx = DDA->nx;
			player->wy = DDA->fx;
		}
		else
		{
			if (DDA->ystep > 0)
				*wdir = DIR_N;
			else
				*wdir = DIR_S;
			player->wx = DDA->gy;
			player->wy = DDA->ny;
		}
		DDA->hit = true;
		return (1);
	}
	return (0);
}

bool	check_hit(t_player *player, dir_t *wdir, t_DDA *DDA, t_info *info)
{
	int	map_type;

	while (DDA->hit != 1)
	{
		DDA->dist_vert = ray_dist(player->x, player->y, DDA->nx, DDA->fx);
		DDA->dist_horiz = ray_dist(player->x, player->y, DDA->gy, DDA->ny);
		map_type = get_map_type(DDA, info);
		if (map_type < 0)
			error_print("out of map");
		if (check_map_type(player, DDA, map_type, wdir))
			break;
		if (DDA->hit_dir == VERT)	
			DDA->nx += DDA->xstep;
		else
			DDA->ny += DDA->ystep;
	}
	return (DDA->hit);
}

bool	hit_wall(double	ray, t_mlx *mlx, dir_t *wdir)
{
	mlx->DDA.xstep = check_zero(cos(ray));
	mlx->DDA.ystep = check_zero(sin(ray));
	mlx->DDA.hit = false;
	get_nx_ny(&mlx->player, &mlx->DDA);
	get_fx_gy(ray, &mlx->player, &mlx->DDA);
	return (check_hit(&mlx->player, wdir, &mlx->DDA, &mlx->info));
}

double	cast_single_ray(int x, t_mlx *mlx, t_player *player, dir_t *wdir)
{
	double	ray;
	double	wdist;

	ray = player->th + (FOV_H / 2) - (x * (FOV_H / (SX - 1))); //ray 각도
	if (hit_wall(ray, mlx, wdir) == false)
		error_print("bad map");
	wdist = ray_dist(player->x, player->y, player->wx, player->wy);
	wdist *= cos(player->th - ray);
	return (wdist);
}

int	ft_render(t_mlx *mlx)
{
	int		x;
	dir_t	wdir;
	double	wdist;

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->background.img, 0, 0);
	while (x < SX)
	{
		wdist = cast_single_ray(x, mlx, &mlx->player, &wdir);
		draw_wall(mlx, wdist, x, wdir);		
		x++;
	}
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
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.background.img, 0, 0);
	// mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, \
	// 		ft_player_move, &mlx.player);
	// mlx_loop_hook(mlx.mlx_ptr, ft_render, &mlx);
	mlx_loop(mlx.mlx_ptr);
    return 0;
}

// int	main(int argc, char** argv)
// {
// 	t_mlx	mlx;

// 	ft_assert(ac == 2, "please input only map file");
// 	mlx.mlx_ptr = mlx_init();
// 	mlx.win = mlx_new_window(mlx.mlx_ptr, SX, SY, "Cub3d");
// 	ft_load_image(&mlx);
// 	make_bg(&mlx);
// 	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, key_event, &mlx.player);
// 	mlx_loop_hook(mlx.mlx_ptr, render, &mlx);
// 	mlx_loop(mlx.mlx_ptr);
// }