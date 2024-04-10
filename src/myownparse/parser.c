/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:57:12 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/10 22:06:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(char *str, char **envp)
{
	t_cmd	*command;
	t_list	*tokens;

	if (!str || !*str || !envp || !*envp)
		return (EXIT_FAILURE);
	command = ft_calloc(1, sizeof(t_cmd));
	tokens = lex_tony(str, envp);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (!validator_tony(tokens))
		return (EXIT_FAILURE);
	return (command);
}
