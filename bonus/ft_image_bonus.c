/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:57:03 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 20:25:12 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static unsigned int	*get_image_addr(t_img *img, int DIR)
{
	unsigned int	*ret;

	ret = (unsigned int *)mlx_get_data_addr(img[DIR].img, &img[DIR].bpp, \
			&img[DIR].line_size, &img[DIR].endian);
	return (ret);
}

void	ft_load_image(t_mlx *mlx)
{
	int	i;

	mlx->imgs[DIR_N].img = mlx_xpm_file_to_image(mlx->mlx_ptr, \
			mlx->info.path[DIR_N], &mlx->imgs[DIR_N].w, &mlx->imgs[DIR_N].h);
	mlx->imgs[DIR_S].img = mlx_xpm_file_to_image(mlx->mlx_ptr, \
			mlx->info.path[DIR_S], &mlx->imgs[DIR_S].w, &mlx->imgs[DIR_S].h);
	mlx->imgs[DIR_W].img = mlx_xpm_file_to_image(mlx->mlx_ptr, \
			mlx->info.path[DIR_W], &mlx->imgs[DIR_W].w, &mlx->imgs[DIR_W].h);
	mlx->imgs[DIR_E].img = mlx_xpm_file_to_image(mlx->mlx_ptr, \
			mlx->info.path[DIR_E], &mlx->imgs[DIR_E].w, &mlx->imgs[DIR_E].h);
	i = -1;
	while (++i < 4)
		ft_assert(mlx->imgs[i].img != NULL, "image Load Error!");
	mlx->imgs[DIR_N].data = get_image_addr(mlx->imgs, DIR_N);
	mlx->imgs[DIR_S].data = get_image_addr(mlx->imgs, DIR_S);
	mlx->imgs[DIR_W].data = get_image_addr(mlx->imgs, DIR_W);
	mlx->imgs[DIR_E].data = get_image_addr(mlx->imgs, DIR_E);
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*bg_color;

	bg_color = (char *)mlx->background.data + \
		(y * mlx->background.line_size + x * (mlx->background.bpp / 8));
	*(unsigned int *)bg_color = color;
}

void	make_bg(t_mlx *mlx)
{
	int	x;
	int	y;

	if (mlx->background.img == NULL)
	{
		mlx->background.img = mlx_new_image(mlx->mlx_ptr, SX, SY);
		ft_assert(mlx->background.img != NULL, "image new error!");
		mlx->background.data = (unsigned int *)mlx_get_data_addr \
				(mlx->background.img, &mlx->background.bpp, \
					&mlx->background.line_size, &mlx->background.endian);
	}
	x = -1;
	while (++x < SX)
	{
		y = -1;
		while (++y < SY)
		{
			if (y / (SY / 2) == 0)
				pixel_put(mlx, x, y, mlx->info.ceilling_color);
			else
				pixel_put(mlx, x, y, mlx->info.floor_color);
		}
	}
}
