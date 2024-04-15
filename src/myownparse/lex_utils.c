/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:59:23 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/15 22:30:42 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

int	check_syntax_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*store_syntax_char(char *str, int *i)
{
	int	j;
	int	start;

	j = 1;
	if ((str[*i] == str[*i + 1]) && (str[(*i)] == '>' || str[(*i)] == '<'))
	{
		(*i)++;
		j++;
	}
	start = (*i) - j + 1;
	(*i)++;
	return (ft_substr(str, start, j));
}

void	*clear_all(t_list **list, char *error)
{
	if (*list)
		ft_lstclear(list, free);
	ft_puterror_noexit(error);
	return (NULL);
}

int	check_sign_char(t_list *list)
{
	t_list	*last;
	char	*str;

	if (!list)
		return (0);
	last = ft_lstlast(list);
	str = (char *)last->content;
	if (str[1] == str[0] && (str[1] == '>' || str[1] == '<'))
		return (1);
	return (0);
}

char	*create_string(char *str, int j, int *i)
{
	int			x;
	int			flag;
	const char	*meta_chars;

	x = j;
	meta_chars = "><|";
	flag = 0;
	while (x < (*i) && str[x])
		if (ft_strchr(meta_chars, str[x++]))
			flag = 1;
	if (flag == 1)
		return (ft_substr(str, j, *i - j));
	return (ft_substr(str, j + 1, *i - j - 2));
}
