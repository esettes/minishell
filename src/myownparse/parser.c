/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:07 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/16 16:17:30 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_closed(char *line, int i, char quote)
{
	while (line[++i])
	{
		if (line[i] == quote)
			return (i);
	}
	return (-1);
}

char	*manage_quotes(char *line, int *i, char quote)
{
	int	j;

	j = quotes_closed(line, *i, quote);
	if (j == -1)
		return (free(line), print_err_msg(quote), NULL);
	return (remove_quotes_metachar(i, j, line, quote));
}

char	*quotes_checker(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[0] == PIPE || (line[i] == PIPE && line[i + 1] == PIPE)
			|| (line[i] == PIPE && !is_blank_line(&line[i + 1])))
			return (free(line), print_err_msg(PIPE), NULL);
		else if (line[i] == DOUBLE_QUOTE)
			line = manage_quotes(line, &i, DOUBLE_QUOTE);
		else if (line[i] == SIMPLE_QUOTE)
			line = manage_quotes(line, &i, SIMPLE_QUOTE);
		if (!line)
			return (NULL);
	}
	return (line);
}
