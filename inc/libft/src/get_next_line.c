/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:44:37 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 10:59:26 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_free(t_gnl **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_free(&(*lst)->next, del);
	del((*lst)->buff_str);
	free(*lst);
	*lst = NULL;
}

t_gnl	*ft_lstlast_gnl(t_gnl *lst)
{
	t_gnl	*temp;

	temp = lst;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

static void	ft_lst_back(t_gnl **lst, char *content)
{
	t_gnl	*last;
	t_gnl	*node;

	last = ft_lstlast_gnl(*lst);
	node = (t_gnl *)malloc(sizeof(t_gnl));
	if (!node)
	{
		free(content);
		return ;
	}
	if (*lst == NULL)
		*lst = node;
	else
		last->next = node;
	node->buff_str = content;
	node->next = NULL;
}

int	lst_init(int fd, t_gnl **list)
{
	int		bytes_read;
	char	*buff;

	while (!find_next_line(*list))
	{
		buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buff)
			return (1);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 1)
		{
			free(buff);
			return (0);
		}
		buff[bytes_read] = '\0';
		ft_lst_back(list, buff);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*str;
	static t_gnl	*list;
	int				count;
	int				flag;

	if (fd < 0 || read(fd, &str, 0) < 0 || BUFFER_SIZE < 1)
		return (ft_free(&list, free), NULL);
	flag = lst_init(fd, &list);
	if (list == NULL || flag == 1)
		return (ft_free(&list, free), NULL);
	count = ft_count_chars(list);
	str = (char *)malloc(count + 1);
	if (!str)
		return (ft_free(&list, free), NULL);
	ft_create_str(list, str);
	clean_create_rest_node(&list);
	return (str);
}
