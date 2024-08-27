/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:59:23 by antosanc          #+#    #+#             */
/*   Updated: 2024/08/27 17:43:45 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

int	check_syntax_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

t_token_lst	*store_syntax_char(char *str, t_token *token)
{
	int			j;
	int			start;
	t_token_lst	*token_lst;

	j = 1;
	token_lst = token_new();
	if ((str[token->i] == str[token->i + 1]) && (str[token->i] == '>'
			|| str[token->i] == '<'))
	{
		token->i++;
		j++;
	}
	start = token->i - j + 1;
	token->i++;
	token_lst->content = ft_substr(str, start, j);
	return (token_lst);
}

void	*clear_all(t_token **token, char *error)
{
	if ((*token)->token_lst)
		token_clear(&((*token)->token_lst), free);
	free(*token);
	*token = NULL;
	if (error)
		ft_puterror_noexit(error);
	return (NULL);
}

int	check_heredoc(t_token_lst *token_lst)
{
	t_token_lst	*last;
	char		*str;

	if (!token_lst)
		return (0);
	last = token_last(token_lst);
	str = last->content;
	if (ft_strlen(str) >= 2 && str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}

t_token_lst	*create_token_lst(char *str, int j, t_token **token, int flag)
{
	t_token_lst	*token_lst;

	token_lst = token_new();
	token_lst->content = ft_substr(str, j, (*token)->i - j);
	if (check_heredoc((*token)->token_lst))
		return (token_lst);
	if (str[j] && str[j] == '$' && (str[j + 1] == '\0' || str[j + 1] == '\"'))
	{
		token_lst->content = ft_substr(str, j, (*token)->i - j);
		return (token_lst);
	}
	if (j > 0 && str[j - 1] && !((str[j - 1] == '\'')))
	{
		if (flag > 0)
			while (flag-- > 0)
				token_lst->content = expander(token_lst->content,
						(*token)->envp, token);
	}
	if (!*token_lst->content)
	{
		free(token_lst->content);
		free(token_lst);
		token_lst = NULL;
	}
	return (token_lst);
}
