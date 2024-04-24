/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/19 21:50:04 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_process(char **cmd, char *envp[], char *path_envp)
{
	char	*path;

	if (cmd_have_path(cmd[0]))
	{
		path = f_strdup(cmd[0]);
		if (execve(path, cmd, envp) < 0)
			return (f_error());
		return (EXIT_SUCCESS);
	}
	path = get_path(cmd[0], path_envp);
	if ((cmd_have_current_path(cmd[0]) || !path))
	{
		free_split(cmd);
		g_signal = 127;
		return (127);
	}
	if (execve(path, cmd, envp) < 0)
	{
		printf("Execve error\n");
		return (f_error());
	}
	return (EXIT_SUCCESS);
}

int	run_child(t_pipe *data, t_cmd *cmd, char *envp[], int pos)
{
	close(data->pip[R]);
	if (duplicate_fd(data->pip[W], STDOUT_FILENO))
		return (EXIT_FAILURE);
	close(data->pip[W]);
	if (dup_files(&data->infile, &data->outfile))
		return (EXIT_FAILURE);
	if (is_parent_exec(data->cmd[0]))
	{
		if (run_parent(cmd, &data, pos))
			exit(f_error());
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		if (exec_process(data->cmd, envp, data->envp))
			exit(f_error());
	}
	return (EXIT_SUCCESS);
}

int	run_child2(t_pipe *data, t_cmd *cmd, char *envp[], int pos)
{
	close(data->pip[W]);
	if (duplicate_fd(data->pip[R], STDIN_FILENO))
		return (EXIT_FAILURE);
	close(data->pip[R]);
	if (dup_files(&data->infile, &data->outfile))
		return (EXIT_FAILURE);
	if (is_parent_exec(data->last_cmd[0]))
	{
		if (run_parent(cmd, &data, pos))
			exit(f_error());
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		if (exec_process(data->last_cmd, envp, data->envp))
			exit(f_error());
	}
	return (EXIT_SUCCESS);
}
