/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/11 15:43:11 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_process(t_pipe *data, char **cmd)
{
	char	*path;

	if (cmd_have_path(cmd[0]))
	{
		path = f_strdup(cmd[0]);
		if (execve(path, cmd, data->envp_minish) < 0)
			return (f_error());
		return (EXIT_SUCCESS);
	}
	path = get_path(cmd[0], get_env_var_value(data->envp_minish, "PATH"));
	if ((cmd_have_current_path(cmd[0]) || !path))
	{
		free_split(cmd);
		g_signal = 2;
		return (2);
	}
	dprintf(1, "before execve!\n");
	if (execve(path, cmd, data->envp_minish) < 0)
		return (f_error());
	dprintf(1, "after execve!\n");
	if (data->n_cmds == 1)
	{
		close(data->std_[R]);
		close(data->std_[W]);
	}
	return (EXIT_SUCCESS);
}


int	run_child(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd)
{
	if (data->infile)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	else if (pos != 0)
	{
		dup2(data->old_fd, STDIN_FILENO);
		close(data->old_fd);
	}
	if (data->outfile)
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
	else
	{
		close(data->pip[R]);
		dup2(data->pip[W], W);
		close(data->pip[W]);
	}
	if (is_parent_exec(data->cmd[0]))
	{
		if (run_parent(cmd, &data, pos, old_cwd))
			exit(f_error());
	}
	else
	{
		if (exec_process(data, data->cmd))
			exit(f_error());
	}
	dprintf(1, "before close all in run_child!\n");
	close(data->std_[R]);
	close(data->std_[W]);
	close(data->pip[R]);
	close(data->pip[W]);
	return (EXIT_SUCCESS);
}

int	run_child2(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd)
{
	dprintf(1, "single execve command!\n");
	if (data->n_cmds == 1)
	{
		if (data->infile)
		{
			dup2(data->infile, STDIN_FILENO);
			close(data->infile);
		}
		if (data->outfile)
		{
			dup2(data->outfile, STDOUT_FILENO);
			close(data->outfile);
		}
	}
	if (is_parent_exec(data->cmd[0]))
	{
		dprintf(1, "before run_parent!\n");
		run_parent(cmd, &data, pos, old_cwd);
		// if (data->n_cmds > 1)
		// {
		// 	dprintf(1, "last command closing multiple commands!\n");
		// 	close(data->std_[R]);
		// 	close(data->std_[W]);
		// 	close(data->pip[R]);
		// 	close(data->pip[W]);
		// }
		dprintf(1, "after run_parent!\n");
	}
	else
	{
		dprintf(1, "before exec_process!\n");
		exec_process(data, data->cmd);
		dprintf(1, "after exec_process!\n");
	}
	if (data->n_cmds > 1)
	{
		dprintf(1, "last command closing multiple commands!\n");
		close(data->std_[R]);
		close(data->std_[W]);
		close(data->pip[R]);
		close(data->pip[W]);
	}
	exit(g_signal);
	return (EXIT_SUCCESS);
}
