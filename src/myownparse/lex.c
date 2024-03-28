/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:25:09 by ubuntu            #+#    #+#             */
/*   Updated: 2024/03/28 17:35:29 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"


//borrar cuando termine esta parte
volatile int	g_signal = 0;


//No funciona bien, me dice todo el rato unclosed quotes, cuando no deberia, falta revisar.
static char	*quotes_content(char *str, char **envp, int *i, char quote)
{
	(void)envp;
	if (!ft_strchr(str, quote))
		return (ft_puterror_noexit("unclosed quotes"), NULL);
	while (*str != '\'' && *str)
	{
		str++;
		(*i)++;
	}
	return (ft_substr(str, 0, *i));
}

static char	*search_token(char *str, char **envp)
{
	(void)str;
	(void)envp;
	return (NULL);
}

t_list	*lex_tony(char *str, char **envp)
{
	t_list	*list;
	char	*content;
	int		i;

	list = NULL;
	while (*str)
	{
		content = NULL;
		i = 0;
		while (*str == ' ')
			str++;
		if (*str == '\'' || *str == '\"')
		{
			content = quotes_content(str + 1, envp, &i, *str);
			str += i + 1;
			printf("%c\n", *str);
		}
		else
			content = search_token(str, envp);
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
	char	*str = "\'hola que tal\'  \' adios \'";

	list = lex_tony(str, NULL);
	
	while (list)
	{
		printf("content: %s\n", (char *)list->content);
		list = list->next;
	}
	return (0);
}