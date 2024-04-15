/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:24 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/15 22:39:08 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

volatile int	g_signal = 0;

static char	*quotes_content(char *str, char **envp, int *i, t_list **list)
{
	int		j;
	char	*string;
	int		flag;
	char	quote;

	j = *i - 1;
	quote = str[j];
	flag = 0;
	if (!ft_strchr(str + *i, quote))
		return (clear_all(list, "unclosed quotes"));
	while (str[*i] != quote && str[*i])
	{
		if (str[*i] == '$')
			flag++;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	string = create_string(str, j, i);
	if (check_sign_char(*list))
		return (string);
	if (quote == '\"' && flag > 0)
		while (flag-- > 0)
			string = expander_process(string, envp, list);
	return (string);
}

static char	*search_token(char *str, char **envp, int *i, t_list **list)
{
	int		flag;
	int		j;
	char	*string;

	j = *i;
	flag = 0;
	if (check_syntax_char(str[*i]))
		return (store_syntax_char(str, i));
	while (!check_syntax_char(str[*i]) && str[*i])
	{
		if (str[*i] == '$')
			flag++;
		(*i)++;
	}
	string = ft_substr(str, j, *i - j);
	if (check_sign_char(*list))
		return (string);
	if (flag > 0)
		while (flag-- > 0)
			string = expander_process(string, envp, list);
	return (string);
}

t_list	*lex_tony(char *str, char **envp)
{
	t_list	*list;
	char	*content;
	int		i;

	list = NULL;
	i = 0;
	while (str[i])
	{
		content = NULL;
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			content = quotes_content(str, envp, &i, &list);
		}
		else
			content = search_token(str, envp, &i, &list);
		if (content && *content)
			ft_lstadd_back(&list, ft_lstnew(content));
		else if (!content)
			break ;
	}
	return (list);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_list	*list;
	char	*str = " >\">\"";
	t_list	*tmp;

	
	(void)argc;
	(void)argv;
	list = lex_tony(str, envp);
	tmp = list;
	while (list)
	{
		printf("content: %s\n", (char *)list->content);
		list = list->next;
	}
	ft_lstclear(&tmp, free);
	return (0);
}*/