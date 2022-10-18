/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:37:16 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 15:41:08 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_check_valid_rgb(char *rgb_fc)
{
	int	i;
	int	num_count;
	int	comma_count;

	i = 0;
	num_count = 0;
	comma_count = 0;
	while (rgb_fc[i] != '\0')
	{
		if (rgb_fc[i] == ',')
		{
			ft_assert(num_count != 0, "RGB parsing Error!");
			num_count = 0;
			comma_count++;
		}
		else
		{
			ft_assert(ft_isdigit(rgb_fc[i]), "RGB parsing Error!");
			num_count++;
		}
		i++;
	}
	ft_assert(comma_count == 2, "RGB parsing Error!");
}

static int	ft_parse_rgb(char *rgb_fc)
{
	char	**split;
	int		rgb;
	int		rgb_atoi;
	int		i;

	ft_check_valid_rgb(rgb_fc);
	split = ft_split(rgb_fc, ',');
	i = -1;
	while (++i < 3)
	{
		rgb_atoi = ft_atoi(split[i]);
		ft_assert(rgb_atoi >= 0 && rgb_atoi <= 255, "RGB Parsing Error!");
		if (i == 0)
			rgb = rgb_atoi;
		else
			rgb = (rgb << 8) + rgb_atoi;
	}
	ft_split_clear(split);
	return (rgb);
}

void	ft_check_type(t_mlx *mlx, char *line)
{
	static const char	*type[TYPE_LENGTH] = {"NO", "EA", "WE", "SO", "F", "C"};
	static const char	*err_msg = "Duplicate Metadata Error!";
	char				**split;
	int					i;

	split = ft_split(line, ' ');
	ft_assert(split[0] != NULL && split[1] != NULL && \
		(split[2] == NULL || split[2][0] == '\n'), "Map Type Error!");
	i = -1;
	while (++i < TYPE_LENGTH)
	{
		if (ft_strcmp((char *)type[i], split[0]) == 0)
		{
			if (i < 4 && ft_assert(mlx->info.path[i] == NULL, err_msg))
				mlx->info.path[i] = ft_strdup(split[1]);
			if (i == 4 && ft_assert(mlx->info.floor_color == -1, err_msg))
				mlx->info.floor_color = ft_parse_rgb(split[1]);
			if (i == 5 && ft_assert(mlx->info.ceilling_color == -1, err_msg))
				mlx->info.ceilling_color = ft_parse_rgb(split[1]);
			break ;
		}
		ft_assert(i != TYPE_LENGTH - 1, "Metadata Error!");
	}
	ft_split_clear(split);
}
