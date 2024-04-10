/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:25:09 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/10 23:10:14 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

//Heredoc por revisar el tema de expansion de variables de entorno
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
	string = ft_substr(str, j, *i - j);
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
	char	*str = " << adios";
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