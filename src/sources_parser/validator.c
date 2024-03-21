#include "../../inc/headers/minishell.h"

size_t	val_get_type(char *token)
{
	printf("token: %s\n", token);
	if (NULL == token)
		return (ZERO);
	if ('<' == *token || '>' == *token)
		return (T_REDIRECT);
	if ('|' == *token)
		return (T_PIPE);
	if ('\"' == *token || '\'' == *token)
		return (T_QUOTE);	
	return (T_WORLD);
}

static int	ft_check_redirect_heredoc(t_list *tokens)
{
	if ('\0' != ((char *)tokens->content)[1] 
		&& '<' == ((char *)tokens->content)[1])
	{
		if (2 == ft_strlen(tokens->content))
		{
			if (NULL != tokens->next && NULL != tokens->next->next)
				return (EXIT_FAILURE);
		}
		else if (NULL != tokens->next)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	validator(t_list *tokens)//MAYBE NOT FINISHED .. MAYBE NEED MORE VALIDATIONS
{
	size_t	type;
	size_t	last_type;

	type = val_get_type(tokens->content);
	if (T_PIPE == type)
		return (ft_puterror_noexit(ERR_PIPE), EXIT_FAILURE);
	last_type = FALSE;
	while(type)
	{
		if (T_REDIRECT == type)
			if (ft_check_redirect_heredoc(tokens))
				return (ft_puterror_noexit(ERR_NEWLINE), EXIT_FAILURE);
		if (T_REDIRECT == type && type == last_type)
			return (ft_puterror_noexit(ERR_REDIRECT), EXIT_FAILURE);
		if (T_PIPE == type && (T_PIPE == last_type || T_REDIRECT == last_type))
			return (ft_puterror_noexit(ERR_PIPE), EXIT_FAILURE);
		tokens = tokens->next;
		last_type = type;
		if (tokens)
			type = val_get_type(tokens->content);
		else
			break;
	}
	if (T_WORLD != last_type)
		return (ft_puterror_noexit(ERR_NEWLINE), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
