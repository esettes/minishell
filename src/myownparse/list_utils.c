/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:06:08 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/19 22:53:36 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

t_token	*token_init(char **envp)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->i = 0;
	token->envp = envp;
	token->token_lst = NULL;
	return (token);
}

t_token_lst	*token_new(void)
{
	t_token_lst	*node;

	node = (t_token_lst *)malloc(sizeof (t_token_lst));
	if (node == 0)
		return (NULL);
	node->content = NULL;
	node->quotes = 0;
	node->next = NULL;
	return (node);
}

t_token_lst	*token_last(t_token_lst *lst)
{
	t_token_lst	*temp;

	temp = lst;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	token_add_back(t_token_lst **lst, t_token_lst *new)
{
	t_token_lst	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = token_last(*lst);
		last->next = new;
	}
}

void	token_clear(t_token_lst **lst, void (*del)(void *))
{
	t_token_lst	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
