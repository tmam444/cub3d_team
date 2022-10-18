/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:59:27 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 16:21:40 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
