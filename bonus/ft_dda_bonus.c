/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:01:01 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 20:25:07 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_dda_setting(double ray, t_player *player, t_DDA *dda)
{
	dda->xstep = check_zero(cos(ray));
	dda->ystep = check_zero(sin(ray));
	if (dda->xstep > 0)
		dda->nx = floor(player->x) + 1;
	else if (dda->xstep < 0)
		dda->nx = ceil(player->x) - 1;
	else
		dda->nx = player->x;
	if (dda->ystep > 0)
		dda->ny = floor(player->y) + 1;
	else if (dda->ystep < 0)
		dda->ny = ceil(player->y) - 1;
	else
		dda->ny = player->y;
	dda->fx = INFINITY;
	dda->gy = INFINITY;
}

void	ft_calc_next_grid(double ray, t_mlx *mlx, t_player *p)
{
	if (mlx->dda.xstep != 0)
		mlx->dda.fx = tan(ray) * (mlx->dda.nx - p->x) + p->y;
	if (mlx->dda.ystep != 0)
		mlx->dda.gy = (1 / tan(ray)) * (mlx->dda.ny - p->y) + p->x;
	mlx->dda.dist_vert = ray_dist(p->x, p->y, mlx->dda.nx, mlx->dda.fx);
	mlx->dda.dist_horiz = ray_dist(p->x, p->y, mlx->dda.gy, mlx->dda.ny);
	if (mlx->dda.dist_vert < mlx->dda.dist_horiz)
	{
		mlx->dda.map_y = (int) mlx->dda.fx;
		if (mlx->dda.xstep == 1)
			mlx->dda.map_x = (int)(mlx->dda.nx);
		else
			mlx->dda.map_x = (int)(mlx->dda.nx) - 1;
		mlx->dda.hit_dir = VERT;
	}
	else
	{
		mlx->dda.map_x = (int) mlx->dda.gy;
		if (mlx->dda.ystep == 1)
			mlx->dda.map_y = (int)(mlx->dda.ny);
		else
			mlx->dda.map_y = (int)(mlx->dda.ny) - 1;
		mlx->dda.hit_dir = HORIZ;
	}
}

void	ft_setting_hit_value(t_mlx *mlx, t_dir *wdir)
{
	if (mlx->dda.hit_dir == VERT)
	{
		if (mlx->dda.xstep > 0)
			*wdir = DIR_E;
		else
			*wdir = DIR_W;
		mlx->dda.wx = mlx->dda.nx;
		mlx->dda.wy = mlx->dda.fx;
	}
	else
	{
		if (mlx->dda.ystep > 0)
			*wdir = DIR_N;
		else
			*wdir = DIR_S;
		mlx->dda.wx = mlx->dda.gy;
		mlx->dda.wy = mlx->dda.ny;
	}
}

void	calc_bump_wall(double ray, t_dir *wdir, t_mlx *mlx)
{
	int	cell;

	ft_dda_setting(ray, &mlx->player, &mlx->dda);
	while (1)
	{
		ft_calc_next_grid(ray, mlx, &mlx->player);
		cell = map_validate_check(mlx->dda.map_x, mlx->dda.map_y, mlx);
		if (cell == 1)
		{
			ft_setting_hit_value(mlx, wdir);
			return ;
		}
		if (mlx->dda.hit_dir == VERT)
			mlx->dda.nx += mlx->dda.xstep;
		else
			mlx->dda.ny += mlx->dda.ystep;
	}
}

double	cast_single_ray(int x, t_dir *wdir, t_mlx *mlx)
{
	const double	fovh_2 = FOV_H / 2.0;
	const double	ray = (mlx->player.th + fovh_2) - (x * FOV_H / (SX - 1.));
	double			wdist;

	calc_bump_wall(ray, wdir, mlx);
	wdist = ray_dist(mlx->player.x, mlx->player.y, mlx->dda.wx, mlx->dda.wy);
	wdist *= cos(mlx->player.th - ray);
	return (wdist);
}
