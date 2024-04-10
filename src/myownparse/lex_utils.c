#include "../../inc/headers/minishell.h"

int	check_syntax_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
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
