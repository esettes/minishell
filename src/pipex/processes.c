/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/24 23:10:14 by iostancu         ###   ########.fr       */
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
	//dprintf(2, "path: %s\n", path);
	if ((cmd_have_current_path(cmd[0]) || !path))
	{
		printf("no path!\n");
		free_split(cmd);
		g_signal = 2;
		return (2);
	}
	if (execve(path, cmd, data->envp_minish) < 0)
	{
		printf("Execve error\n");
		return (f_error());
	}
	return (EXIT_SUCCESS);
}

int	run_child(t_pipe *data, t_cmd *cmd, int pos)
{
	close(data->pip[R]);
	if (dup2(data->pip[W], STDOUT_FILENO))
		return (EXIT_FAILURE);
	//close(data->pip[W]);
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
		if (exec_process(data, data->cmd))
			exit(f_error());
	}
	return (EXIT_SUCCESS);
}

int	run_child2(t_pipe *data, t_cmd *cmd, int pos)
{
	//close(data->pip[W]);
	if (dup2(data->pip[R], STDIN_FILENO))
		return (EXIT_FAILURE);
	//close(data->pip[R]);
	if (dup_files(&data->infile, &data->outfile))
		return (EXIT_FAILURE);
	if (is_parent_exec(data->last_cmd[0]))
	{
		if (run_parent(cmd, &data, pos))
		{
			printf("builtin error\n");
			exit(f_error());
		}
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		if (exec_process(data, data->last_cmd))
			exit(f_error());
	}
	return (EXIT_SUCCESS);
}
