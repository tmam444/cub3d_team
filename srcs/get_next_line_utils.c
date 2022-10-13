/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:28:37 by chulee            #+#    #+#             */
/*   Updated: 2022/10/13 16:50:50 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_fd_list	*ft_new_fd_lst(int fd)
{
	t_fd_list	*new;

	new = malloc(sizeof(t_fd_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->data = NULL;
	new->next_fd = NULL;
	return (new);
}

t_fd_list	*ft_find_cur(t_fd_list **lst, int fd)
{
	t_fd_list	*temp;

	if (*lst == NULL)
	{
		*lst = ft_new_fd_lst(fd);
		if (*lst == NULL)
			return (NULL);
		return (*lst);
	}
	temp = *lst;
	while (temp != NULL)
	{
		if (temp->fd == fd)
			break ;
		else if (temp->next_fd == NULL)
		{
			temp->next_fd = ft_new_fd_lst(fd);
			if (temp->next_fd == NULL)
				return (NULL);
		}
		temp = temp->next_fd;
	}
	return (temp);
}

void	ft_lstdelone(t_fd_list **lst, int fd)
{
	t_fd_list	*prev;
	t_fd_list	*cur;
	t_data_list	*data_temp;

	prev = *lst;
	cur = *lst;
	while (cur != NULL && cur->fd != fd)
	{
		prev = cur;
		cur = cur->next_fd;
	}
	if (cur == NULL)
		return ;
	while (cur->data != NULL)
	{
		data_temp = cur->data->next_data;
		free(cur->data);
		cur->data = data_temp;
	}
	if (cur != prev)
		prev->next_fd = cur->next_fd;
	else if (cur == prev)
		*lst = cur->next_fd;
	free(cur);
}

int	ft_lstadd_string(t_fd_list *lst, const char *src, int srcsize)
{
	int	status;
	int	i;

	if (srcsize <= 0)
		return (-1);
	status = 1;
	i = 0;
	while (i < srcsize)
	{
		ft_datalstadd_back(&lst->data, src[i]);
		if (src[i] == '\n')
			status = -1;
		i++;
	}
	return (status);
}

t_data_list	*ft_new_data_lst(const char c)
{
	t_data_list	*ret;

	ret = malloc(sizeof(t_data_list));
	if (!ret)
		return (NULL);
	ret->c = c;
	ret->next_data = NULL;
	return (ret);
}
