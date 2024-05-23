/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/23 20:42:52 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_process(t_pipe *data, char **cmd)
{
	char	*path;

	path = get_path(cmd[0], get_env_var_value(data->envp_minish, "PATH"));
	if (!ft_strcmp("1", path))
		return (EXIT_FAILURE);
	if (!ft_strcmp("2", path))
	{
		g_signal = 127;
		print_err_msg(data->last_cmd[0], data->last_cmd[1], "Command not found");
		free_split(cmd);
		exit(127);
	}
	if (execve(path, cmd, data->envp_minish) < 0)
		return (free(path), EXIT_FAILURE);
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
		{
			print_err_msg(data->last_cmd[0], data->last_cmd[1], NULL);
			exit(g_signal);
		}
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
		{
			print_err_msg(data->last_cmd[0], data->last_cmd[1], NULL);
			exit(g_signal);
		}
	}
	return (EXIT_SUCCESS);
}
