// casi terminado falta probarlo y darle una revision
#include "../../inc/headers/minishell.h"

static	void	syntax_error(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'", str);
}

static int	check_error_cases(t_list *tokens)
{
	t_list	*next;
	char	t_current;
	char	t_next;

	next = tokens->next;
	if (!next)
		return (EXIT_SUCCESS);
	t_current = ((char *)tokens->content)[0];
	t_next = ((char *)next->content)[0];
	if (t_current == '|' && t_next == '|')
        return (syntax_error("||"), EXIT_FAILURE);
	if ((t_current == '>' || t_current == '<')
		&& (t_next == '>' || t_next == '<' || t_next == '|'))
		return (syntax_error(next->content), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validator_tony(t_list *tokens)
{
	t_list	*last;

	last = ft_lstlast(tokens);
	if (((char *)tokens->content)[0] == '|')
	if (last && last->content && ((char *)last->content)[0] == '>'
		|| ((char *)last->content)[0] == '<')
		return (syntax_error("newline"), EXIT_FAILURE);
	else if (((char *)tokens->content)[0] == '|'
		|| ((char *)last->content)[0] == '|')
		return (syntax_error("|"), EXIT_FAILURE);
	while (tokens)
	{
		if (check_error_cases(tokens))
			return (EXIT_FAILURE);
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}