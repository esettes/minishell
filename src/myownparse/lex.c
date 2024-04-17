/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:24 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/17 23:28:59 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

volatile int	g_signal = 0;

static t_token_lst	*quotes_content(char *str, t_token *token)
{
	int			j;
	t_token_lst	*token_lst;
	int			flag;
	char		quote;

	j = token->i;
	quote = str[j - 1];
	flag = 0;
	if (!ft_strchr(str + token->i, quote))
		return (clear_all(token, "unclosed quotes"));
	while (str[token->i] != quote && str[token->i])
	{
		if (str[token->i] == '$')
			flag++;
		(token->i)++;
	}
	token_lst = create_token_lst(str, j, token, flag);
	return (token_lst);
}

static t_token_lst	*search_token(char *str, t_token *token)
{
	int			j;
	t_token_lst	*token_lst;
	int			flag;

	j = token->i;
	flag = 0;
	if (check_syntax_char(str[token->i]))
		return (store_syntax_char(str, token));
	while (str[token->i] && !check_syntax_char(str[token->i]))
	{
		if (str[token->i] == '$')
			flag++;
		token->i++;
	}
	token_lst = create_token_lst(str, j, token, flag);
	return (token_lst);
}

t_token	*lex_tony(char *str, char **envp)
{
	t_token		*token;
	t_token_lst	*token_lst;

	token = token_init(envp);
	while (str[token->i])
	{
		token_lst = NULL;
		while (str[token->i] == ' ')
			token->i++;
		if (!str[token->i])
			break ;
		if (str[token->i] == '\'' || str[token->i] == '\"')
		{
			token->i++;
			token_lst = quotes_content(str, token);
		}
		else
			token_lst = search_token(str, token);
    	if (token_lst && token_lst->content && *token_lst->content)
        		token_add_back(&token->token_lst, token_lst);
		else if (!token_lst)
			return (NULL);
	}
	return (token);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*list;
	char	*str = "<< >> a a ";
	t_token_lst	*tmp2;

	(void)argc;
	(void)argv;
	list = lex_tony(str, envp);
	if (!list)
		return (0);
	tmp2 = list->token_lst;
	while (tmp2)
	{
		printf("content: %s\n", tmp2->content);
		printf("quotes: %d\n", tmp2->quotes);
		tmp2 = tmp2->next;
	}
	if (list)
		clear_all(list, NULL);
	return (0);
}