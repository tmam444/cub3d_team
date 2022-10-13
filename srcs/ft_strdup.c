/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:42:59 by youskim           #+#    #+#             */
/*   Updated: 2022/10/13 19:49:48 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*arr;

	len = 0;
	while (str[len])
		len++;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		ft_assert(true, "Malloc Error!");
	len = 0;
	while (str[len])
	{
		arr[len] = str[len];
		len++;
	}
	arr[len] = '\0';
	return (arr);
}
