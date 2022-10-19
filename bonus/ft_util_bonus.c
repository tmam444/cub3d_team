/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:45:59 by youskim           #+#    #+#             */
/*   Updated: 2022/10/19 14:51:23 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

void	ft_clear_mlx(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (mlx->imgs[i].img)
			mlx_destroy_image(mlx->mlx_ptr, mlx->imgs[i].img);
	if (mlx->background.img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->background.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
}

int	ft_assert(int check, const char *err_msg)
{
	if (!check)
	{
		write(2, "Error\n", 6);
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		exit(1);
	}
	return (1);
}

int	map_validate_check(int x, int y, t_mlx *mlx)
{
	if (x >= 0 && x < mlx->info.map_h && y >= 0 && y < mlx->info.map_w)
		return (mlx->info.map[x][y]);
	else
		return (-1);
}

void	ft_split_clear(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
