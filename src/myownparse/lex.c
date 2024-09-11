/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:24 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/11 20:06:57 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static t_token_lst	*search_token(char *str, t_token **token);
//int	g_signal = 0;
static t_token_lst	*quotes_content(char *str, t_token **token)
{
	int			j;
	int			i;
	t_token_lst	*token_lst;
	int			flag;
	char		quote;
	int			n_quotes;

	j = (*token)->i;
	quote = str[j - 1];
	flag = 0;
	n_quotes = 0;
	i = 0;
	if (!ft_strchr(str + (*token)->i, quote))
		return (clear_all(token, "unclosed quotes"));
	if (str[(*token)->i - 2] == ' ')
	{
		i = (*token)->i;
		while (str[i] != '"')
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
	return (search_token(str, token));
	//return (token_lst);
}

static char	*remove_quotes(char *str)
{
	int		n_quotes;
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = 0;
	n_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			n_quotes++;
	}
	ret = malloc(sizeof(char) * (ft_strlen(str) - n_quotes));
	i = 0;
	while (str[i])
	{
		if (str[i] != '"')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	free (str);
	return (ret);
}

static t_token_lst	*search_token(char *str, t_token **token)
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
		
		if (str[(*token)->i] == '\"')
			(*token)->i++;
		if (str[(*token)->i] == '$')
			flag++;
		(*token)->i++;
	}
	if ((*token)->single_arg == TRUE)
	{
		// get len of 1st token
		(*token)->limit.start = ft_strlen((*token)->token_lst->content) + 1;
		
		str = remove_quotes(str);
		(*token)->limit.end = ft_strlen(str);
			
		(*token)->i = (*token)->limit.end;
		token_lst = create_token_lst_single(str, (*token)->limit.start, token, flag);
		
		return (token_lst);
	}
	token_lst = create_token_lst(str, j, token, flag);
	return (token_lst);
}

t_token	*lex_tony(char *str, char **envp)
{
	t_token		*token;
	t_token_lst	*token_lst;

	token = token_init(envp);
	while (str[token->i] && token->single_arg == FALSE)
	{
		//dprintf(1, "lex_tony str[token->i]: %c\n", str[token->i]);
		token_lst = NULL;
		while (str[token->i] == ' ')
			token->i++;
		if (!str[token->i])
			break ;
		if (str[token->i] == '\'' || str[token->i] == '\"')
		{
			token->i++;
			token_lst = quotes_content(str, &token);
		}
		else
		{
			token_lst = search_token(str, &token);
		
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

void	set_single_arg_token(t_token **token, t_token_lst *t_list)
{
	if (t_list && t_list->content && *t_list->content
			|| t_list && t_list->quotes == 1)
			token_add_back(&(*token)->token_lst, t_list);
		if (token == NULL)
			return ;
}
/*int	main(int argc, char **argv, char **envp)
{
	t_token	*list;
	char	*str = "hola \'$a\' adios\" venga\"";
	t_token_lst	*str2;

	(void)argc;
	(void)argv;
	list = lex_tony(str, envp);
	if (!list)
		return (0);
	str2 = list->token_lst;
	while (str2)
	{
		printf("content: %s\n", str2->content);
		printf("quotes: %d\n", str2->quotes);
		str2 = str2->next;
	}
	if (list)
		clear_all(&list, NULL);
	return (0);
}*/