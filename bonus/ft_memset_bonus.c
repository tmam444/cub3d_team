/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:45:05 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 20:25:23 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	a;
	unsigned char	*str;
	size_t			i;

	a = (unsigned char)c;
	str = (unsigned char *)b;
	i = 0;
	while (i < n)
	{
		str[i] = a;
		i++;
	}
	return (str);
}
