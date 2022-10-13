/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:48:00 by youskim           #+#    #+#             */
/*   Updated: 2022/10/13 20:50:38 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_check_valid_rgb(char *rgb_fc)
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

static int ft_parse_rgb(char *rgb_fc)
{
	char	**split;
	int		rgb;
	int		rgb_atoi;
	int		i;

	// , 갯수가 2개인지
	// ',', 숫자인지
	
	// 숫자,,숫자
	// 숫자,숫자,숫자
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

static void	ft_check_type(t_mlx *mlx, char *line)
{
	static const char	*type[TYPE_LENGTH] = {"NO", "EA", "WE", "SO", "F", "C"};
	char				**split;
	int					i;

	split = ft_split(line, ' ');
	printf("line = %s, split[0] = %s, split[1] = %s, split[2] = %s\n", line, split[0], split[1], split[2]);
	ft_assert(split[0] != NULL && split[1] != NULL && (split[2] == NULL || split[2][0] == '\n'), \
													"Map Type Error!");
	i = -1;
	while (++i < TYPE_LENGTH)
	{
		if (ft_strcmp(split[0], (char *)type[i]) == 0)
		{
			if (i < 4 && ft_assert(mlx->info.path[i] == NULL, \
								"Duplicate Metadata Error!"))
				mlx->info.path[i] = ft_strdup(split[1]);
			else if (i == 4 && ft_assert(mlx->info.floor_color == -1, \
								"Duplicate Metadata Error!"))
				mlx->info.floor_color = ft_parse_rgb(split[1]);
			else if (i == 5 && ft_assert(mlx->info.ceilling_color == -1, \
								"Duplicate Metadata Error!"))
				mlx->info.ceilling_color = ft_parse_rgb(split[1]);
		}
	}
	ft_split_clear(split);
}

static void ft_check_map_data(t_mlx *mlx, char *map_data)
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
			
		}
	}
	ft_split_clear(split);
}

void	ft_check_line_feed(char *map_data)
{
	int	i;
	int	line_count;
	int	char_count;

	line_count = 0;
	char_count = 0;
	i = -1;
	while (map_data[++i] != '\0')
	{
		write(2, map_data + i , 1);
		if (map_data[i] == '\n')
		{
			if (char_count > 0)
				line_count++;
			if (line_count >= 7)
				ft_assert(char_count != 0, "Map error because in line feed");
			char_count = 0;
		}
		else
			char_count++;
	}
	ft_assert(map_data[--i] == '\n', "Map error because in line feed");
}

void	ft_parsing(t_mlx *mlx, char *file)
{
	int		map_fd;
	char	*line;
	char	*map_data;
	char	*temp;

	map_fd = open(file, O_RDONLY);
	ft_assert(map_fd != -1 , "File Open Error");
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
}
