/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:42:59 by youskim           #+#    #+#             */
/*   Updated: 2022/10/18 17:25:41 by chulee           ###   ########.fr       */
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
	ft_assert(arr != NULL, "Malloc Error!");
	len = 0;
	while (str[len])
	{
		arr[len] = str[len];
		len++;
	}
	arr[len] = '\0';
	return (arr);
}
