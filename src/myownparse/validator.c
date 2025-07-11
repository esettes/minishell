/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:34 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/19 22:51:05 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// casi terminado falta probarlo y darle una revision
#include "../../inc/headers/minishell.h"

static void	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
}

static int	check_error_cases(t_token_lst *tokens)
{
	t_token_lst	*next;
	char		t_current;
	char		t_next;

	next = tokens->next;
	if (!next)
		return (EXIT_SUCCESS);
	t_current = ((char *)tokens->content)[0];
	t_next = ((char *)next->content)[0];
	if (t_current == '|' && tokens->quotes == 0 && t_next == '|'
		&& next->quotes == 0)
		return (syntax_error("||"), EXIT_FAILURE);
	if ((t_current == '>' || t_current == '<') && tokens->quotes == 0
		&& (t_next == '>' || t_next == '<' || t_next == '|')
		&& next->quotes == 0)
		return (syntax_error(next->content), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validator_tony(t_token *token)
{
	t_token_lst	*last;
	t_token_lst	*token_lst;

	last = token_last(token->token_lst);
	token_lst = token->token_lst;
	if (last && last->content && last->quotes == 0
		&& (((char *)last->content)[0] == '>'
		|| ((char *)last->content)[0] == '<'))
		return (syntax_error("newline"), EXIT_FAILURE);
	if ((((char *)token_lst->content)[0] == '|' && token_lst->quotes == 0)
		|| (((char *)last->content)[0] == '|' && last->quotes == 0))
		return (syntax_error("|"), EXIT_FAILURE);
	while (token_lst)
	{
		if (check_error_cases(token_lst))
			return (EXIT_FAILURE);
		token_lst = token_lst->next;
	}
	return (EXIT_SUCCESS);
}
