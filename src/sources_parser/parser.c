#include "../../inc/headers/minishell.h"

static int	parse_core(t_cmd *cmd, char *str, char **envp)
{
	t_list	*tokens;

	tokens = lex(str, envp);
	if (NULL == tokens)
		return (EXIT_FAILURE);
	if (validator(tokens))
		return (ft_lstclear(&tokens, &free), EXIT_FAILURE);
	cmd = yacc(cmd, tokens);
	if (NULL == cmd)
		return (ft_lstclear(&tokens, &free), EXIT_FAILURE);
	return (ft_lstclear(&tokens, &free), EXIT_SUCCESS);
}

t_cmd	*parser(char *str, char **envp)
{
	t_cmd	*command;

	if (NULL == str || '\0' == *str || NULL == envp || NULL == *envp)
		return (NULL);
	command = (t_cmd *)ft_calloc(TRUE, sizeof(t_cmd));
	if (NULL != command)
	{
		if (parse_core(command, str, envp))
		{
			free (command);
			command = NULL;
		}
	}
	return (command);
}
