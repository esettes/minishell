#include "../../inc/headers/minishell.h"

static char	*search_next_space(char *s)
{
	char	*a;

	a = s;
	if (*a && (('<' == *a && '<' == *(a + 1)) || ('>' == *a && '>' == *(a + 1))))
		return (a + TRUE);
	while (*a)
	{
		if (ft_isspace(*a) || '|' == *a || '$' == *a || '\'' == *a || '\"' == *a || '<' == *a || '>' == *a)
			return (a);
		a++;
	}
	return (a);
}

static char	*search_end(char *str, char end)
{
	while (str && *str)
	{
		str = ft_strchr(str, end);
		if (str)
<<<<<<< HEAD
			return (str + TRUE);
=======
			return (str + 1);
>>>>>>> 543440311a181f8f35912cb123a41f9052856f30
	}
	return (NULL);
}

static char	*lex_type(char *str)//
{
	char	*end;

	if ('\"' == *str)
		end = search_end(str + 1, '\"');
	else if ('\'' == *str)
		end = search_end(str + 1, '\'');
	else if ('$' == *str)
		end = search_next_space(str + 1);
	else
	{
		end = search_next_space(str);
		if (*str == *end)
			end++;
	}
	if (end)
		return (ft_substr(str, ZERO, end - str));
	return (ft_puterror_noexit("unclosed quotes"), NULL);
}

t_list	*lex(char *str, char **envp)
{
	t_list	*lex_list;
	t_list	*new;
	char	*descomposed;
	t_list	*tmp;

	lex_list = NULL;
	while (ft_isspace(*str))
		str++;
	while (str && *str)
	{
		descomposed = lex_type(str);
		if (NULL == descomposed)
			return (ft_lstclear(&lex_list, &free), NULL); 
		str += ft_strlen(descomposed);
		descomposed = expander(descomposed, envp);
		new = ft_lstnew(descomposed);
		if (new && descomposed)//leak
			ft_lstadd_back(&lex_list, new);
		else
		{
			ft_lstclear(&lex_list, &free);
			lex_list = NULL;
			break ;
		}
		while (ft_isspace(*str))
			str++;
	}
<<<<<<< HEAD
	printf("lex_list: \n");
=======
>>>>>>> 543440311a181f8f35912cb123a41f9052856f30
	tmp = lex_list;
	while (tmp)
	{
		printf("content: %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (lex_list);
}
