/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:59:27 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 20:25:16 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double	ft_deg_to_rad(double d)
{
	return (d * M_PI / 180.0);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	ft_max(double a, double b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
