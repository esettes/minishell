/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:07 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/13 09:03:30 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static int	parse_checker(t_cmd *cmd, char *str, char **envp, char *newbuff)
{
	t_token		*token;
	t_token_lst	*head;

	token = lex_tony(str, envp, newbuff);
	
	if (token->single_arg == TRUE)
	{
		//dprintf(1,"token->single_arg: %i\n", token->single_arg);
		cmd->single_arg = TRUE;
	}
	dprintf(1, "newbuff after lex_tony: %s\n", newbuff);
	dprintf(1,"str after lex_tony: %s\n", str);
	if (token == NULL)
	{
		exit_s = 2;
		return (EXIT_FAILURE);
	}
	if (validator_tony(token))
	{
		exit_s = 2;
		return (clear_all(&token, NULL), EXIT_FAILURE);
	}
	head = token->token_lst;
	cmd = yacc_tony(cmd, &token->token_lst, envp);
	token->token_lst = head;
	if (cmd == NULL)
		return (clear_all(&token, NULL), EXIT_FAILURE);
	return (clear_all(&token, NULL), EXIT_SUCCESS);
}

t_cmd	*parser(char *str, char **envp, char *newbuff)
{
	t_cmd	*command;
	int		error_h;

	if (!str || !*str)
		return (NULL);
	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	if (parse_checker(command, str, envp, newbuff))
		return (free_cmd_tony(command), NULL);
	//dprintf(1,"cmd single arg: %i\n", command->single_arg);
	//dprintf(1,"parser newbuff: %s\n", newbuff);
	dprintf(1,"parser buffer: %s\n", str);
	return (command);
}
