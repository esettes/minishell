/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:34 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/12 17:30:32 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// casi terminado falta probarlo y darle una revision
#include "../../inc/headers/minishell.h"

static void	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
}

static int	check_error_cases(t_list *tokens)
{
	t_list	*next;
	char	t_current;
	char	t_next;

	next = tokens->next;
	if (!next)
		return (EXIT_SUCCESS);
	t_current = ((char *)tokens->content)[0];
	t_next = ((char *)next->content)[0];
	if (t_current == '|' && t_next == '|')
        return (syntax_error("||"), EXIT_FAILURE);
	if ((t_current == '>' || t_current == '<')
		&& (t_next == '>' || t_next == '<' || t_next == '|'))
		return (syntax_error(next->content), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validator_tony(t_list *tokens)
{
	t_list	*last;

	last = ft_lstlast(tokens);
	if (last && last->content && (((char *)last->content)[0] == '>'
		|| ((char *)last->content)[0] == '<'))
		return (syntax_error("newline"), EXIT_FAILURE);
	if (((char *)tokens->content)[0] == '|'
		|| ((char *)last->content)[0] == '|')
		return (syntax_error("|"), EXIT_FAILURE);
	while (tokens)
	{
		if (check_error_cases(tokens))
			return (EXIT_FAILURE);
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}