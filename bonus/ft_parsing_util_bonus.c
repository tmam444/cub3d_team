/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_util_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:37:53 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 20:25:28 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_setting_player(t_mlx *mlx, int x, int y, char th)
{
	ft_assert(mlx->player.x == -1, "Player Duplicate Error");
	mlx->player.x = x;
	mlx->player.y = y;
	if (th == 'E')
		mlx->player.th = ft_deg_to_rad(0);
	else if (th == 'N')
		mlx->player.th = ft_deg_to_rad(90);
	else if (th == 'W')
		mlx->player.th = ft_deg_to_rad(180);
	else if (th == 'S')
		mlx->player.th = ft_deg_to_rad(270);
}

void	ft_rotate_player(t_mlx *mlx, int **new_map)
{
	int	temp;

	mlx->info.map = new_map;
	temp = mlx->info.map_w;
	mlx->info.map_w = mlx->info.map_h;
	mlx->info.map_h = temp;
	temp = mlx->player.x;
	mlx->player.x = mlx->player.y + 0.5;
	mlx->player.y = (int)fabs((double)temp - (mlx->info.map_w - 1)) + 0.5;
}
