/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:16:37 by chulee            #+#    #+#             */
/*   Updated: 2021/11/26 02:51:20 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data_list{
	char				c;
	struct s_data_list	*next_data;
}	t_data_list;

typedef struct s_fd_list{
	int					fd;
	struct s_data_list	*data;
	struct s_fd_list	*next_fd;
}	t_fd_list;

char		*get_next_line(int fd);
t_fd_list	*ft_new_fd_lst(int fd);
t_fd_list	*ft_find_cur(t_fd_list **lst, int fd);
t_data_list	*ft_new_data_lst(const char c);
void		ft_lstdelone(t_fd_list **lst, int fd);
int			ft_lstadd_string(t_fd_list *lst, const char *src, int srcsize);
void		ft_datalstadd_back(t_data_list **lst, const char c);
int			ft_datalst_size(t_data_list *lst);
char		*ft_datalst_to_str(t_data_list **lst);

#endif
