/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:50:48 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 15:04:56 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init(t_mlx *mlx)
{
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->info.floor_color = -1;
	mlx->info.ceilling_color = -1;
	mlx->player.x = -1;
	mlx->player.y = -1;
	mlx->player.th = -1;
}

void	ft_file_type_check(char *filename)
{
	static const char	*file_type = ".cub";
	int					i;
	int					len;

	len = ft_strlen(filename);
	i = ft_strlen(file_type);
	ft_assert(len > i, "File Type Error");
	while (i > 0)
		ft_assert(filename[--len] == file_type[--i], "File Type Error");
}

int	main(int ac, char **av)
{
	t_mlx		mlx;

	ft_assert(ac == 2, "please input only map file");
	ft_file_type_check(av[1]);
	ft_init(&mlx);
	ft_parsing(&mlx, av[1]);
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, SX, SY, "A simple example");
	ft_load_image(&mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, \
			ft_key_event, &mlx);
	mlx_hook(mlx.win, 17, 0, &ft_program_exit, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, ft_render, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
