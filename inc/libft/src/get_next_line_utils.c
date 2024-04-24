/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:44:46 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 10:54:29 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_clean_rest(t_gnl **lst, char *buff, t_gnl *rest_node)
{
	t_gnl	*next;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->buff_str);
		free((*lst));
		*lst = next;
	}
	*lst = NULL;
	if (rest_node->buff_str[0])
		*lst = rest_node;
	else
	{
		free(buff);
		free(rest_node);
	}
}

int	ft_count_chars(t_gnl *lst)
{
	int	i;
	int	count;

	count = 0;
	while (lst)
	{
		i = 0;
		while (lst->buff_str[i])
		{
			if (lst->buff_str[i] == '\n')
			{
				count++;
				return (count);
			}
			i++;
			count++;
		}
		lst = lst->next;
	}
	return (count);
}

int	find_next_line(t_gnl *lst)
{
	int	i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->buff_str[i] && i < BUFFER_SIZE)
		{
			if (lst->buff_str[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_create_str(t_gnl *lst, char *array)
{
	int		i;
	int		j;

	j = 0;
	if (!array)
		return ;
	while (lst)
	{
		i = 0;
		while (lst->buff_str[i])
		{
			if (lst->buff_str[i] == '\n')
			{
				array[j] = '\n';
				array[++j] = '\0';
				return ;
			}
			array[j] = lst->buff_str[i];
			i++;
			j++;
		}
		lst = lst->next;
	}
	array[j] = '\0';
}

void	clean_create_rest_node(t_gnl **lst)
{
	t_gnl	*last_node;
	t_gnl	*rest_node;
	char	*str;
	int		i;
	int		j;

	last_node = ft_lstlast_gnl(*lst);
	rest_node = (t_gnl *)malloc(sizeof(t_gnl));
	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!rest_node || !str)
	{
		free(str);
		free(rest_node);
		return (ft_free(lst, free));
	}
	i = 0;
	j = 0;
	while (last_node->buff_str[i] && last_node->buff_str[i] != '\n')
		i++;
	while (last_node->buff_str[i] && last_node->buff_str[++i])
		str[j++] = last_node->buff_str[i];
	str[j] = '\0';
	rest_node->buff_str = str;
	rest_node->next = NULL;
	ft_clean_rest(lst, str, rest_node);
}
