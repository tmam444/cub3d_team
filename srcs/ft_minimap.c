/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:31:48 by youskim           #+#    #+#             */
/*   Updated: 2022/10/19 14:32:41 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_set_color(t_mlx *mlx, int *color, int i, int j)
{
	*color = 0xFF0000;
	if (i >= 0 && i < mlx->info.map_h && j >= 0 && j < mlx->info.map_w)
	{
		if (i == (int)mlx->player.x && j == (int)mlx->player.y)
			*color = 0xFFFF00;
		else if (mlx->info.map[i][j] == 0)
			*color = 0x0000FF;
		else if (mlx->info.map[i][j] == 1)
			*color = 0xFF0000;
	}
}

static void	ft_put_minimap(t_mlx *mlx, int start_x, int start_y, int color)
{
	const int	margin = SX / 55;
	const int	size = SX / 50;
	int			i;
	int			j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win, \
			(margin + (start_x - ((int)mlx->player.x - 2)) * size) + i, \
			(int)fabs(((double)((start_y - ((int)mlx->player.y - 2)) * size) + \
			j - size * 5)) + margin, color);
			j++;
		}
		i++;
	}
}

void	ft_render_minimap(t_mlx *mlx)
{
	int	color;
	int	start_x;
	int	start_y;

	color = 0x000000;
	start_x = (int)mlx->player.x - 2;
	while (start_x < (int)mlx->player.x + 3)
	{
		start_y = (int)mlx->player.y - 2;
		while (start_y < (int)mlx->player.y + 3)
		{
			ft_set_color(mlx, &color, start_x, start_y);
			ft_put_minimap(mlx, start_x, start_y, color);
			start_y++;
		}
		start_x++;
	}
}
