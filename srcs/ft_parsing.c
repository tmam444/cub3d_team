/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:48:00 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 19:41:46 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_map(t_mlx *mlx, char **split)
{
	ft_check_empty_line(split);
	ft_map_size_check(mlx, split);
	ft_save_map(mlx, split);
	ft_check_map_surround_wall(mlx);
	ft_check_validate(mlx);
	ft_rotate_map(mlx);
}

static void	ft_check_map_data(t_mlx *mlx, char *map_data)
{
	char				**split;
	int					i;
	int					meta_count;

	split = ft_split(map_data, '\n');
	i = -1;
	meta_count = 0;
	while (split[++i] != NULL)
	{
		if (meta_count++ < 6)
			ft_check_type(mlx, split[i]);
		else
		{
			ft_init_map(mlx, split + i);
			break ;
		}
	}
	ft_split_clear(split);
}

static void	ft_check_line_feed(char *map_data)
{
	int	i;
	int	line_count;
	int	char_count;

	line_count = 0;
	char_count = 0;
	i = -1;
	while (map_data[++i] != '\0')
	{
		if (map_data[i] == '\n')
		{
			if (char_count > 0)
				line_count++;
			if (line_count >= 7)
				ft_assert(char_count != 0, "Map error");
			char_count = 0;
		}
		else
			char_count++;
	}
	ft_assert(map_data[--i] == '\n', "Map error");
}

void	ft_parsing(t_mlx *mlx, char *file)
{
	int		map_fd;
	char	*line;
	char	*map_data;
	char	*temp;

	map_fd = open(file, O_RDONLY);
	ft_assert(map_fd != -1, "File Open Error");
	map_data = NULL;
	line = get_next_line(map_fd);
	while (line != NULL)
	{
		temp = map_data;
		map_data = ft_strjoin(map_data, line);
		free(temp);
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	ft_check_line_feed(map_data);
	ft_check_map_data(mlx, map_data);
	free(map_data);
	ft_assert(mlx->info.map != NULL && mlx->info.map_w > 0, "Map Data Error!");
}
