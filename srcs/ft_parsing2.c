/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:37:12 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 19:43:21 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_map_size_check(t_mlx *mlx, char **split)
{
	int	i;
	int	max_width;

	i = -1;
	max_width = 0;
	while (split[++i] != NULL)
	{
		if (max_width < (int)ft_strlen(split[i]))
			max_width = ft_strlen(split[i]);
	}
	mlx->info.map_h = i;
	mlx->info.map_w = max_width;
	mlx->info.map = malloc(sizeof(int *) * mlx->info.map_h);
	ft_assert(mlx->info.map != NULL, "Malloc Error!");
	i = -1;
	while (++i < mlx->info.map_h)
	{
		mlx->info.map[i] = malloc(sizeof(int) * mlx->info.map_w);
		ft_assert(mlx->info.map[i] != NULL, "Malloc Error!");
		ft_memset(mlx->info.map[i], -1, mlx->info.map_w * sizeof(int));
	}
}

void	ft_save_map(t_mlx *mlx, char **split)
{
	int	i;
	int	j;

	i = -1;
	while (split[++i] != NULL)
	{
		j = -1;
		while (split[i][++j] != '\0')
		{
			ft_assert(ft_strchr("01EWSN ", split[i][j]) != NULL, \
					"Map Error");
			if (ft_strchr("EWSN", split[i][j]) != NULL)
				ft_setting_player(mlx, i, j, split[i][j]);
			if (ft_strchr("0EWSN", split[i][j]) != NULL)
				mlx->info.map[i][j] = 0;
			else if (split[i][j] == '1')
				mlx->info.map[i][j] = 1;
			else if (split[i][j] == ' ')
				mlx->info.map[i][j] = -1;
		}
	}
	ft_assert(mlx->player.x != -1, "Player empty!");
}

void	ft_rotate_map(t_mlx *mlx)
{
	int	**temp;
	int	i;
	int	j;

	temp = malloc(sizeof(int *) * mlx->info.map_w);
	ft_assert(temp != NULL, "Malloc Error!");
	i = 0;
	while (i < mlx->info.map_w)
	{
		temp[i] = malloc(sizeof(int) * mlx->info.map_h);
		ft_assert(temp[i] != NULL, "Malloc Error!");
		j = 0;
		while (j < mlx->info.map_h)
		{
			temp[i][j] = mlx->info.map[mlx->info.map_h - 1 - j][i];
			j++;
		}
		i++;
	}
	ft_clear(mlx);
	ft_rotate_player(mlx, temp);
}
