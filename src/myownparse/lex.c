/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:24 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/13 10:14:22 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static t_token_lst	*search_token(char *str, t_token **token, char **newbuff);
static char	*remove_quotes(char *str);

static t_token_lst	*quotes_content(char *str, t_token **token, char *newbuff)
{
	int			j;
	int			i;
	t_token_lst	*token_lst;
	int			flag;
	char		quote;
	int			n_quotes;
	int			n_dquotes;

	j = (*token)->i;
	quote = str[j - 1];
	dprintf(1, "quote: %c\n", quote);
	flag = 0;
	n_quotes = 0;
	n_dquotes = 0;
	i = 0;
	if (!ft_strchr(str + (*token)->i, quote))
		return (clear_all(token, "unclosed quotes"));
	if (str[(*token)->i - 2] == ' ')// && ft_strlen(str) - 1 == ' ')
	{
		i = (*token)->i;
		while (str[i] != '"' && str[i] != '\'')
			i++;
		if (!str[i + 1] || (str[i + 1] && str[i + 1] == ' '))
		{
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
	}
	(*token)->single_arg = TRUE;
	return (search_token(str, token, &newbuff));
	//return (token_lst);
}

static t_token_lst	*search_token(char *str, t_token **token, char **newbuff)
{
	int			j;
	t_token_lst	*token_lst;
	int			flag;
	int			start;
	int			end;

	j = (*token)->i;
	flag = 0;
	start = 0;
	end = 0;
	if (check_syntax_char(str[(*token)->i]))
		return (store_syntax_char(str, *token));
	while (str[(*token)->i] && !check_syntax_char(str[(*token)->i]))
	{
		dprintf(1, "-------> %c\n", str[(*token)->i]);
		if (str[(*token)->i] == '\"' )
			(*token)->i++;
		if (str[(*token)->i] == '$')
			flag++;
		(*token)->i++;
	}
	//if ((*token)->single_arg == TRUE)
	///{
		// get len of 1st token
		(*token)->limit.start = ft_strlen((*token)->token_lst->content) + 1;
		
		//str = remove_quotes(str);
		//(*newbuff) = remove_quotes(str);
		//dprintf(1, "newbuff after remove_quotes: %s\n", (*newbuff));
		(*token)->limit.end = ft_strlen(str);
			
		(*token)->i = (*token)->limit.end;
		token_lst = create_token_lst_single(str, (*token)->limit.start, token, flag);
		
		return (token_lst);
	//}
	token_lst = create_token_lst(str, j, token, flag);
	return (token_lst);
}

t_token	*lex_tony(char *str, char **envp, char *newbuff)
{
	t_token		*token;
	t_token_lst	*token_lst;

	token = token_init(envp);
	while (str && str[token->i])// && token->single_arg == FALSE)
	{
		token_lst = NULL;
		while (str[token->i] == ' ')
			token->i++;
		if (!str[token->i])
			break ;
		if (str[token->i] == '\'' || str[token->i] == '\"')
		{
			token->i++;
			token_lst = quotes_content(str, &token, newbuff);
		}
		else
		{
			token_lst = search_token(str, &token, &newbuff);
			//dprintf(1, "newbuff after search_token: %s\n", newbuff);
		}
		if (token_lst && token_lst->content && *token_lst->content
			|| token_lst && token_lst->quotes == 1)
			token_add_back(&token->token_lst, token_lst);
		if (token == NULL)
			return (NULL);
	}
	// if (token->single_arg == TRUE)
	// {
	// 	set_single_arg_token(token, token_lst);
	// }
	return (token);
}
