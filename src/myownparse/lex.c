/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:25:09 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/02 23:05:13 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"


//borrar cuando termine esta parte
volatile int	g_signal = 0;

static char	*quotes_content(char *str, char **envp, int *i, char quote)
{
	int		j;
	char	*string;
	int		flag;

	(*i)++;
	j = *i;
	flag = 0;
	if (!ft_strchr(str + j, quote))
		return (ft_puterror_noexit("unclosed quotes"), NULL);
	while (str[*i] != quote && str[*i])
	{
		if (str[*i] == '$')
			flag++;
		(*i)++;
	}
	string = ft_substr(str + j, 0, *i - j);
	if (quote == '\"' && flag > 0)
		while (flag-- > 0)
			string = expander_process(string, envp);
	return (string);
}

static char	*search_token(char *str, char **envp, int *i)
{
	(void)str;
	(void)envp;
	(void)i;
	return (NULL);
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
		if (str[i] == '\'' || str[i] == '\"')
		{
			content = quotes_content(str, envp, &i, str[i]);
			printf("%s\n", content);
			i++;
		}
		else
			content = search_token(str, envp, &i);
		if (!content)
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		ft_lstadd_back(&list, ft_lstnew(content));
	}
	return (list);
}

int	main(void)
{
	t_list	*list;
	char	*str = "\'hola que tal\'  \' adios \' \'       \'";

	list = lex_tony(str, NULL);
	
	while (list)
	{
		printf("content: %s\n", (char *)list->content);
		list = list->next;
	}
	return (0);
}