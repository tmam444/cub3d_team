/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:43:06 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 14:43:52 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_player_rotate(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		player->th += 1 * ROT_UNIT;
	else if (keycode == KEY_RIGHT)
		player->th -= 1 * ROT_UNIT;
    if (player->th < 0)
		player->th += _2PI;
    else if (player->th > _2PI)
		player->th -= _2PI;
	return (0);
}

int	ft_move_wasd(int keycode, t_player *player)
{
	if (keycode == KEY_W)
	{
		player->x += MOVE_UNIT * cos(player->th);
		player->y += MOVE_UNIT * sin(player->th);
	}
	else if (keycode == KEY_S)
	{
		player->x -= MOVE_UNIT * cos(player->th);
		player->y -= MOVE_UNIT * sin(player->th);
	}
	else if (keycode == KEY_D)
	{
		player->x += MOVE_UNIT * cos(player->th - M_PI_2);
		player->y += MOVE_UNIT * sin(player->th - M_PI_2);
	}
	else if (keycode == KEY_A)
	{
		player->x += MOVE_UNIT * cos(player->th + M_PI_2);
		player->y += MOVE_UNIT * sin(player->th + M_PI_2);
	}
	return (0);
}


int	ft_player_move(int keycode, t_mlx *mlx)
{
	t_player	temp;

	temp.x = mlx->player.x;
	temp.y = mlx->player.y;
	temp.th = mlx->player.th;
	ft_player_rotate(keycode, &mlx->player);
	ft_move_wasd(keycode, &temp);
	if (map_validate_check(temp.x, temp.y, mlx) == 0)
	{
		mlx->player.x = temp.x;
		mlx->player.y = temp.y;
	}
	return (0);
}

int	ft_key_event(int keycode, t_mlx *mlx)
{
	int	i;

	if (keycode == KEY_ESC)
	{
		ft_clear(mlx);
		exit(0);
	}
	else
		ft_player_move(keycode, mlx);
	return (0);
}

int	ft_program_exit(t_mlx *mlx)
{
	ft_clear(mlx);
	exit(0);
}
