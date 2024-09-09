/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:24 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/09 20:57:17 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

//int	g_signal = 0;
static t_token_lst	*quotes_content(char *str, t_token **token)
{
	int			j;
	t_token_lst	*token_lst;
	int			flag;
	char		quote;

	j = (*token)->i;
	quote = str[j - 1];
	flag = 0;
	// si el total del argumento està entre comillas, entonces quotes
	
	if (!ft_strchr(str + (*token)->i, quote))
		return (clear_all(token, "unclosed quotes"));
	// coge la str mientras !=; añadir q debe haber espacio delante del 1er quote y detras del 2º (o NULL)
	// añadiendo un if, si es así entrar al while, sino return search_token
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
	//if (str[(*token)->i] == '\"' && str[(*token)->i - 1] )
	if (check_syntax_char(str[(*token)->i]))
		return (store_syntax_char(str, *token));
	while (str[(*token)->i] && !check_syntax_char(str[(*token)->i]))
	{
		
		if (str[(*token)->i] == '\"')
			(*token)->i++;
		dprintf(1, "%c\n", str[(*token)->i]);
		if (str[(*token)->i] == '$')
			flag++;
		(*token)->i++;
	}
	// funct q elimine quotes y retorne new str para pasarlo a createÇ_token_lst
	// !!
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
		//invertir if st.
		if (str[token->i] == '\'' || str[token->i] == '\"')
		{
			token->i++;
			token_lst = quotes_content(str, &token);
		}
		else
			token_lst = search_token(str, &token);
		if (token_lst && token_lst->content && *token_lst->content
			|| token_lst && token_lst->quotes == 1)
			token_add_back(&token->token_lst, token_lst);
		if (token == NULL)
			return (NULL);
	}
	return (token);
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