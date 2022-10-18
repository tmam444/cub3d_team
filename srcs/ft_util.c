/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:45:59 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 14:48:17 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int map_validate_check( int x, int y, t_mlx *mlx)
{
	if (x >= 0 && x < mlx->info.map_h && y >= 0 && y < mlx->info.map_w)
		return (mlx->info.map[x][y]);
	else
		return (-1);
}