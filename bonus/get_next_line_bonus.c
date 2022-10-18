/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:49:47 by chulee            #+#    #+#             */
/*   Updated: 2022/10/18 20:24:45 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*cur;
	char				*ret;
	char				temp[BUFFER_SIZE + 1];
	int					read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cur = ft_find_cur(&head, fd);
	if (!cur)
		return (NULL);
	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, temp, BUFFER_SIZE);
		if (ft_lstadd_string(cur, temp, read_size) == -1)
			break ;
	}
	ret = ft_datalst_to_str(&cur->data);
	if (cur->data == NULL && read_size <= 0)
		ft_lstdelone(&head, fd);
	return (ret);
}

void	ft_datalstadd_back(t_data_list **lst, const char c)
{
	t_data_list	*temp;

	if (*lst == NULL)
	{
		*lst = ft_new_data_lst(c);
		return ;
	}
	temp = *lst;
	while (temp->next_data != NULL)
		temp = temp->next_data;
	temp->next_data = ft_new_data_lst(c);
	return ;
}

int	ft_datalst_size(t_data_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		if (lst->c == '\n')
			break ;
		lst = lst->next_data;
	}
	return (i);
}

char	*ft_datalst_to_str(t_data_list **lst)
{
	t_data_list	*temp;
	char		*ret;
	int			size;
	int			i;

	size = ft_datalst_size(*lst);
	if (size == 0)
		return (NULL);
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (*lst != NULL)
	{
		ret[i] = (*lst)->c;
		temp = (*lst)->next_data;
		free(*lst);
		*lst = temp;
		if (ret[i++] == '\n')
			break ;
	}
	ret[i] = '\0';
	return (ret);
}
