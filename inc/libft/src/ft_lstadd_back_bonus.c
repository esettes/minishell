/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uliherre <uliherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:46:15 by uherrero          #+#    #+#             */
/*   Updated: 2023/12/28 21:57:51 by uliherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new) 
{
	t_list	*current;
	if (lst == NULL || new == NULL)
	{
		printf("Error: Argumento nulo en ft_lstadd_back.\n");
		exit(EXIT_FAILURE);
	}
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	ft_lstadd_back_d(t_list_d **lst, t_list_d **new)
{
	if (NULL != new && NULL != lst)
	{
		*lst = (t_list_d *) ft_lstlast((t_list *) *lst);
		if (NULL == *lst)
			*lst = *new;
		else
		{
			(*lst)->next = *new;
			(*new)->prev = *lst;
		}
	}
}
