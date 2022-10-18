/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:37:09 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 20:25:33 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	ft_check_validate_func(t_mlx *mlx, int i, int j)
{
	if (i - 1 >= 0)
		ft_assert(mlx->info.map[i - 1][j] == 1 || \
				mlx->info.map[i - 1][j] == -1, "Map error!");
	if (i + 1 < mlx->info.map_h)
		ft_assert(mlx->info.map[i + 1][j] == 1 || \
				mlx->info.map[i + 1][j] == -1, "Map error!");
	if (j + 1 < mlx->info.map_w)
		ft_assert(mlx->info.map[i][j + 1] == 1 || \
				mlx->info.map[i][j + 1] == -1, "Map error!");
	if (j - 1 >= 0)
		ft_assert(mlx->info.map[i][j - 1] == 1 || \
				mlx->info.map[i][j - 1] == -1, "Map error!");
	if (i - 1 >= 0 && j - 1 >= 0)
		ft_assert(mlx->info.map[i - 1][j - 1] == 1 || \
				mlx->info.map[i - 1][j - 1] == -1, "Map error!");
	if (i - 1 >= 0 && j + 1 < mlx->info.map_w)
		ft_assert(mlx->info.map[i - 1][j + 1] == 1 || \
				mlx->info.map[i - 1][j + 1] == -1, "Map error!");
	if (i + 1 < mlx->info.map_h && j - 1 >= 0)
		ft_assert(mlx->info.map[i + 1][j - 1] == 1 || \
				mlx->info.map[i + 1][j - 1] == -1, "Map error!");
	if (i + 1 < mlx->info.map_h && j + 1 < mlx->info.map_w)
		ft_assert(mlx->info.map[i + 1][j + 1] == 1 || \
				mlx->info.map[i + 1][j + 1] == -1, "Map error!");
}

void	ft_check_validate(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->info.map_h)
	{
		j = -1;
		while (++j < mlx->info.map_w)
		{
			if (mlx->info.map[i][j] == -1)
				ft_check_validate_func(mlx, i, j);
		}
	}
}

void	ft_check_map_surround_wall(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->info.map_h)
	{
		j = -1;
		while (++j < mlx->info.map_w)
		{
			if (i == 0 || i == mlx->info.map_h - 1)
				ft_assert(mlx->info.map[i][j] == 1 || \
					mlx->info.map[i][j] == -1, "Map Must Surround wall Error");
			else if (j == 0 || j == mlx->info.map_w - 1)
				ft_assert(mlx->info.map[i][j] == 1 || \
					mlx->info.map[i][j] == -1, "Map Must Surround wall Error");
		}
	}
}

void	ft_check_empty_line(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		ft_assert(ft_strchr(split[i], '1') != NULL, "Map Error");
		i++;
	}
}
