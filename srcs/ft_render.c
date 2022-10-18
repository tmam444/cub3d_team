/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:01:02 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 17:51:51 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_wall_height(double wdist)
{
	const double	fov_h = 2.0 * wdist * tan(FOV_V / 2.0);

	return ((int)(SY * (WALL_H / fov_h)));
}

static double	calc_txratio(t_mlx *mlx, t_dir wdir)
{
	if (wdir == DIR_W || wdir == DIR_E)
		return (mlx->dda.wy - floor(mlx->dda.wy));
	else
		return (mlx->dda.wx - floor(mlx->dda.wx));
}

static void	draw_wall(t_mlx *mlx, double wdist, int x, t_dir wdir)
{
	int	wall_height;
	int	y[2];
	int	y_start_end[2];
	int	tx_ty[2];

	wall_height = get_wall_height(wdist);
	y[0] = (int)((SY - wall_height) / 2);
	y[1] = y[0] + wall_height - 1;
	y_start_end[0] = ft_max(0, y[0]);
	y_start_end[1] = ft_min(SY - 1, y[1]);
	tx_ty[0] = (int)(calc_txratio(mlx, wdir) * 64);
	while (y_start_end[0] < y_start_end[1])
	{
		tx_ty[1] = ((double)y_start_end[0] - y[0]) * 64 / wall_height;
		if (wdir == DIR_W || wdir == DIR_N)
			pixel_put(mlx, x, y_start_end[0], \
					mlx->imgs[wdir].data[tx_ty[1] * 64 + tx_ty[0]]);
		else
			pixel_put(mlx, x, y_start_end[0], \
					mlx->imgs[wdir].data[tx_ty[1] * 64 - tx_ty[0]]);
		y_start_end[0] += 1;
	}
}

void	ft_render_minimap(t_mlx *mlx)
{
	int	color;
	color = 0x000000;
	for (int k = 0; k < 32; k++)
	{
		for (int i = 0; i < 32; i++)
		{
			if (i == 0 || k == 0 || k == 31 || i == 31)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win, 10 + i, 10 + k, 0xFFFFFF);
			else
				mlx_pixel_put(mlx->mlx_ptr, mlx->win, 10 + i, 10 + k, color);
		}
	}
	int	start_x = mlx->player.x - 2;
	int	start_y = mlx->player.y - 2;
	for (int i = mlx->player.x - 2; i < mlx->player.x + 3; i++)
	{
		for (int j = mlx->player.y - 2; j < mlx->player.y + 3; j++)
		{
			color = 0xFF0000;
			if (i >= 0 && i < mlx->info.map_h && j >= 0 && j < mlx->info.map_w)
			{
				if (i == (int)mlx->player.x && j == (int)mlx->player.y)
					color = 0xFFFF00;
				else if (mlx->info.map[i][j] == 0)
					color = 0x0000FF;
				else if (mlx->info.map[i][j] == 1)
					color = 0xFF0000;
			}
			for (int k = 0; k < 5; k++)
			{
				for (int g = 0; g < 5; g++)
				{
					mlx_pixel_put(mlx->mlx_ptr, mlx->win, 11 + ((j - start_y) * 5) + g, \
							11 + ((i - start_x) * 5) + k, color);
				}
			}
		}
	}
}

int	ft_render(t_mlx *mlx)
{
	t_dir	wdir;
	double	wdist;
	int		x;

	make_bg(mlx);
	x = 0;
	while (x < SX)
	{
		wdist = cast_single_ray(x, &wdir, mlx);
		draw_wall(mlx, wdist, x, wdir);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->background.img, 0, 0);
	ft_render_minimap(mlx);
	return (0);
}
