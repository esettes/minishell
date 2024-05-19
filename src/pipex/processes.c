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

//no devuelve  No such file or directory
int	exec_process(t_pipe *data, char **cmd)
{
	char	*path;

	if (cmd_have_path(cmd[0]))
	{
		path = f_strdup(cmd[0]);
		if (execve(path, cmd, data->envp_minish) < 0)
		{
			free(path);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	path = get_path(cmd[0], get_env_var_value(data->envp_minish, "PATH"));
	if ((cmd_have_current_path(cmd[0]) || !path))
	{
		g_signal = 127;
		print_err_msg(data->last_cmd[0], data->last_cmd[1], "Command not found");
		free_split(cmd);
		exit(127);
	}
	if (execve(path, cmd, data->envp_minish) < 0)
	{
		printf("Execve error\n");
		return (f_error());
	}
	return (EXIT_SUCCESS);
}

int	run_child(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd)
{
	close(data->pip[R]);
	if (dup2(data->pip[W], STDOUT_FILENO))
		return (EXIT_FAILURE);
	close(data->pip[W]);
	if (dup_files(&data->infile, &data->outfile))
		return (EXIT_FAILURE);
	if (is_parent_exec(data->cmd[0]))
	{
		if (run_parent(cmd, &data, pos, old_cwd))
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

int	run_child2(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd)
{
	close(data->pip[W]);
	if (dup2(data->pip[R], STDIN_FILENO))
		return (EXIT_FAILURE);
	close(data->pip[R]);
	if (dup_files(&data->infile, &data->outfile))
		return (EXIT_FAILURE);
	if (is_parent_exec(data->last_cmd[0]))
	{
		if (run_parent(cmd, &data, pos, old_cwd))
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
