/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/11 23:33:21 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipe	*init_pipe_struct(char *envp[])
{
	t_pipe	*tmp;

	tmp = malloc(sizeof(t_pipe));
	if (tmp == NULL)
		if (f_error())
			return (NULL);
	tmp->envp = getenv("PATH");
	if (tmp->envp == NULL)
		tmp->envp = NULL;
	init_envp_minishell(tmp, envp);
	return (tmp);
}

int	open_file(t_cmd *cmd, t_pipe *data, int pos)
{
	if (cmd->scmd[pos]->in_f)
	{
		data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
		if (data->infile < 0)
			return (f_error());
	}
	else
		data->infile = -1;
	if (cmd->scmd[pos]->out_f)
	{
		data->outfile = open(cmd->scmd[0]->out_f,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile < 0)
			return (f_error());
	}
	else
		data->outfile = -1;
	return (EXIT_SUCCESS);
}

void	close_files(int *infile, int *outfile)
{
	if (*infile > -1)
		close(*infile);
	if (*outfile > -1)
		close(*outfile);
}

int	dup_files(int *infile, int *outfile)
{
	if (*infile > -1)
		if (dup2(*infile, 0) < 0)
			return (f_error());
	if (*outfile > -1)
		if (dup2(*outfile, 1) < 0)
			return (f_error());
	return (EXIT_SUCCESS);
}
