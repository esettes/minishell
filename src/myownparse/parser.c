/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:07 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/13 12:49:05 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"


//Borrar cuando termine de probar
static void	print_result(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("content: %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

static int	parse_checker(t_cmd *cmd, char *str, char **envp)
{
	t_list	*tokens;

	(void)cmd;
	tokens = lex_tony(str, envp);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (validator_tony(tokens))
		return (ft_lstclear(&tokens, free), EXIT_FAILURE);
	cmd = yacc_tony(cmd, tokens);
	if (cmd == NULL)
		return (ft_lstclear(&tokens, free), EXIT_FAILURE);
	print_result(tokens);
	return (ft_lstclear(&tokens, free), EXIT_SUCCESS);
}

t_cmd	*parser(char *str, char **envp)
{
	t_cmd	*command;
	

	if (!str || !*str || !envp || !*envp)
		return (NULL);
	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	if (parse_checker(command, str, envp))
	{
		g_signal = 2;
		return (free(command), NULL);
	}
	return (command);
}

//Borrar cuando termine de probar
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str = "hola | | adios";
	parser(str, envp);
}