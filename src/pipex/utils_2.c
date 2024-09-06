/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/06 22:37:46 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipe	*init_pipe_struct(char *envp[])
{
	t_pipe	*tmp;

	tmp = malloc(sizeof(t_pipe));
	if (tmp == NULL)
		return (NULL);
	init_envp_minishell(tmp, envp);
	tmp->envp = get_env_var_value(tmp->env_mini, "PATH");
	tmp->cmd = NULL;
	tmp->infile = 0;
	tmp->outfile = 0;
	tmp->pid = -1;
	tmp->pid2 = -1;
	tmp->childs = NULL;
	tmp->std_[0] = 0;
	tmp->std_[1] = 0;
	tmp->old_fd = 0;
	tmp->cmd_counter = 0;
	return (tmp);
}

int	open_file(t_cmd *cmd, t_pipe *data, int pos)
{
	if (data->infile)
		(close(data->infile), data->infile = 0);
	if (cmd->scmd[pos]->in_f)
		data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY);
	if (data->outfile)
		(close(data->outfile), data->outfile = 0);
	if (cmd->scmd[pos]->out_f)
	{
		if (cmd->scmd[pos]->append)
			data->outfile = open(cmd->scmd[pos]->out_f, O_APPEND | O_CREAT | O_WRONLY, 0644);
		else
			data->outfile = open(cmd->scmd[pos]->out_f, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	}
	if (data->infile == -1 || data->outfile == -1)
	{
		return (f_error(data));
	}
	return (EXIT_SUCCESS);
	// if (cmd->scmd[pos]->in_f)
	// {
	// 	data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
	// 	if (data->infile < 0)
	// 		return (f_error());
	// }
	// else
	// 	data->infile = -1;
	// if (cmd->scmd[pos]->out_f)
	// {
	// 	if (cmd->scmd[pos]->append)
	// 	{
	// 		data->outfile = open(cmd->scmd[pos]->out_f,
	// 			O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 			dprintf(2, "fd: %d\n", data->outfile);
	// 	}
	// 	else
	// 		data->outfile = open(cmd->scmd[pos]->out_f,
	// 			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (data->outfile < 0)
	// 		return (f_error());
	// }
	// else
	// 	data->outfile = -1;
	// return (EXIT_SUCCESS);
}

void	close_files(int *infile, int *outfile)
{
	if (*infile)
	{
		close(*infile);
		*infile = 0;
	}
	if (*outfile)
	{
		close(*outfile);
		*outfile = 0;
	}
}

// int	dup_files(int *infile, int *outfile)
// {
// 	if (*infile > -1)
// 		if (dup2(*infile, 0) < 0)
// 			return (f_error(data));
// 	if (*outfile > -1)
// 		if (dup2(*outfile, 1) < 0)
// 			return (f_error());
// 	return (EXIT_SUCCESS);
// }

int	cmd_have_relative_path(char *cmd)
{
	register int	i;

	i = 0;
	while (cmd[i])
		if (cmd[i++] == '.')
			return (TRUE);
	return (FALSE);
}
