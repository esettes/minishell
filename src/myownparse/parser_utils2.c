/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:22:03 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/16 19:23:54 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int value)
{
	return (value << 8);
}

void	close_fds(t_pipe *data)
{
	if (data->infile)
		(close(data->infile), data->infile = 0);
	if (data->outfile)
		(close(data->outfile), data->outfile = 0);
}

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
		free(dp[i++]);
	free(dp);
}

int	cmd_counter(char **all_cmd)
{
	int	i;

	i = 0;
	while (all_cmd[i])
		i++;
	return (i);
}

int	is_blank_line(char *line)
{
	int	i;

	if (!ft_strncmp(line, "\"\"\0", 3) || !ft_strncmp(line, "''\0", 3))
		return (0);
	i = -1;
	while (line[++i])
	{
		if (!ft_isblank(line[i]))
			return (1);
	}
	return (0);
}
