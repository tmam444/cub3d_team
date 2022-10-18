/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:47:53 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 14:48:07 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_zero(double d)
{
	if (fabs(d) < EPS)
	{
		return (0);
	}
	else
	{
		if (d > 0)
			return (1);
		else
			return (-1);
	}	
}

double	ray_dist(double player_x, double player_y, double x, double y)
{
	double	dx;
	double	dy;

	dx = player_x - x;
	dy = player_y - y;
	return (sqrt(dx*dx + dy*dy));
}
