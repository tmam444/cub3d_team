/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:48:00 by youskim           #+#    #+#             */
/*   Updated: 2022/10/17 20:08:29 by youskim          ###   ########.fr       */
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

static int	ft_parse_rgb(char *rgb_fc)
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
	//printf("line = %s, split[0] = %s, split[1] = %s, split[2] = %s\n", line, split[0], split[1], split[2]);
	ft_assert(split[0] != NULL && split[1] != NULL && (split[2] == NULL || split[2][0] == '\n'), \
													"Map Type Error!");
	i = -1;
	while (++i < TYPE_LENGTH)
	{
		if (ft_strcmp((char *)type[i], split[0]) == 0)
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
			break ;
		}
		ft_assert(i != TYPE_LENGTH - 1, "Metadata Error!");
	}
	ft_split_clear(split);
}

void	ft_map_size_check(t_mlx *mlx, char **split)
{
	int	i;
	int	max_width;

	i = -1;
	max_width = 0;
	while (split[++i] != NULL)
	{
		if (max_width < ft_strlen(split[i]))
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

void	ft_setting_player(t_mlx *mlx, int x, int y, char th)
{
	ft_assert(mlx->player.x == -1, "Player Duplicate Error");
	mlx->player.x = x;
	mlx->player.y = y;
	if (th == 'E')
		mlx->player.th = deg2rad(0);
	else if (th == 'N')
		mlx->player.th = deg2rad(90);
	else if (th == 'W')
		mlx->player.th = deg2rad(180);
	else if (th == 'S')
		mlx->player.th = deg2rad(270);
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
			ft_assert(ft_strchr("01EWSN ", split[i][j]) != NULL, "Map Element Error");
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

void	ft_check_validate_func(t_mlx *mlx, int i, int j)
{
	if (i - 1 >= 0)
		ft_assert(mlx->info.map[i - 1][j] == 1 || mlx->info.map[i - 1][j] == -1, "Map error!");
	if (i + 1 < mlx->info.map_h)
		ft_assert(mlx->info.map[i + 1][j] == 1 || mlx->info.map[i + 1][j] == -1, "Map error!");
	if (j + 1 < mlx->info.map_w)
		ft_assert(mlx->info.map[i][j + 1] == 1 || mlx->info.map[i][j + 1] == -1, "Map error!");
	if (j - 1 >= 0)
		ft_assert(mlx->info.map[i][j - 1] == 1 || mlx->info.map[i][j - 1] == -1, "Map error!");
	if (i - 1 >= 0 && j - 1 >= 0)
		ft_assert(mlx->info.map[i - 1][j - 1] == 1 || mlx->info.map[i - 1][j - 1] == -1, "Map error!");
	if (i - 1 >= 0 && j + 1 < mlx->info.map_w)
		ft_assert(mlx->info.map[i - 1][j + 1] == 1 || mlx->info.map[i - 1][j + 1] == -1, "Map error!");
	if (i + 1 < mlx->info.map_h && j - 1 >= 0)
		ft_assert(mlx->info.map[i + 1][j - 1] == 1 || mlx->info.map[i + 1][j - 1] == -1, "Map error!");
	if (i + 1 < mlx->info.map_h && j + 1 < mlx->info.map_w)
		ft_assert(mlx->info.map[i + 1][j + 1] == 1 || mlx->info.map[i + 1][j + 1] == -1, "Map error!");
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
				ft_assert(mlx->info.map[i][j] == 1 \
						|| mlx->info.map[i][j] == -1, "Map Must Surround wall Error");
			else if (j == 0 || j == mlx->info.map_w - 1)
				ft_assert(mlx->info.map[i][j] == 1 \
						|| mlx->info.map[i][j] == -1, "Map Must Surround wall Error");
		}
	}
}

void	ft_check_empty_line(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		if (split[i][0] != '\n')
			ft_assert(ft_strchr(split[i], '1') != NULL, "Map Parsing Error");
		i++;
	}
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
	mlx->info.map = temp;
	i = mlx->info.map_w;
	mlx->info.map_w = mlx->info.map_h;
	mlx->info.map_h = i;
	i = mlx->player.x;
	mlx->player.x = mlx->player.y + 0.5;
	mlx->player.y = (int)fabs((double)i - (mlx->info.map_w - 1)) + 0.5;
}

void	ft_init_map(t_mlx *mlx, char **split)
{
	ft_check_empty_line(split);
	ft_map_size_check(mlx, split);
	ft_save_map(mlx, split);
	ft_check_map_surround_wall(mlx);
	ft_check_validate(mlx);
	ft_rotate_map(mlx);
	// for (int i = 0; i < mlx->info.map_h; i++)
	// {
	// 	for (int j = 0; j < mlx->info.map_w; j++)
	// 	{
	// 		if (i == (int)mlx->player.x && j == (int)mlx->player.y)
	// 			printf("P");
	// 		else if (mlx->info.map[i][j] == -1)
	// 			printf("x");
	// 		else if (mlx->info.map[i][j] == 0)
	// 			printf("0");
	// 		else if (mlx->info.map[i][j] == 1)
	// 			printf("1");
	// 	}
	// 	printf("\n");
	// }
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
}
