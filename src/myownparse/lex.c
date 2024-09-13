/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:24 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/13 13:30:27 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

#include "../../inc/headers/minishell.h"
//int	g_signal = 0;
static t_token_lst	*quotes_content(char *str, t_token **token, int pos)
{
	int			j;
	t_token_lst	*token_lst;
	int			flag;
	char		quote;
	int			i;


	j = (*token)->i;
	quote = str[j - 1];
	flag = 0;
	i = 0;
	if (!ft_strchr(str + (*token)->i, quote))
		return (clear_all(token, "unclosed quotes"));
	if (!(str[(*token)->i - 2] == ' '))// && ft_strlen(str) - 1 == ' ')
	{
		i = (*token)->i;
		while (!(str[i] != '"' && str[i] != '\''))
			i++;
		if (!(!str[i + 1] || (str[i + 1] && str[i + 1] == ' ')))
		{
			dprintf(1, "quotes_content says its single arg!\n");
			(*token)->single_arg = TRUE;
		}
	}
	while (str[(*token)->i] && str[(*token)->i] != quote)
	{
		if (str[(*token)->i] == '$')
			flag++;
		((*token)->i)++;
	}
	token_lst = create_token_lst(str, j, token, flag);
	if (token_lst)
		token_lst->quotes = 1;
	(*token)->i++;
	return (token_lst);
}

static t_token_lst	*search_token(char *str, t_token **token)
{
	int			j;
	t_token_lst	*token_lst;
	int			flag;

	j = (*token)->i;
	flag = 0;
	if (check_syntax_char(str[(*token)->i]))
		return (store_syntax_char(str, *token));
	while (str[(*token)->i] && !check_syntax_char(str[(*token)->i]))
	{
		if (str[(*token)->i] == '$')
			flag++;
		(*token)->i++;
	}
	token_lst = create_token_lst(str, j, token, flag);
	return (token_lst);
}
t_token	*lex_tony(char *str, char **envp, char *newbuff, int n_cmds)
{
	t_token		*token;
	t_token_lst	*token_lst;
	int			pos;
	
	pos = 0;
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
			token_lst = quotes_content(str, &token, pos);
		}
		else
			token_lst = search_token(str, &token);
		if (token_lst && token_lst->content && *token_lst->content
			|| token_lst && token_lst->quotes == 1)
		{
			token_add_back(&token->token_lst, token_lst);
			pos++;
		}
		if (token == NULL)
			return (NULL);
	}
	return (token);
}