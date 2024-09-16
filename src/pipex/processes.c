/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/16 16:48:57 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_multiple_cmds(t_pipe *data);

void	wait_cmds(t_pipe *data)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd)
		process_waiting(data);
}

void	redirect_child(t_pipe *data, int i)
{
	if (data->infile)
		(dup2(data->infile, STDIN_FILENO), close(data->infile));
	else if (i != 0)
		(dup2(data->old_fd, 0), close(data->old_fd));
	if (data->outfile)
		(dup2(data->outfile, STDOUT_FILENO), close(data->outfile));
	else if (i != data->n_cmd - 1)
		(close(data->pipe[0]), dup2(data->pipe[1], 1), close(data->pipe[1]));
}

int	exec_cmd(t_pipe *data, char **cmd)
{
	int	status;

	status = 0;
	if (!cmd[0])
		return (free_dp(cmd), 1);
	if (!ft_strncmp(cmd[0], "pwd\0", 4))
		exec_pwd();
	else if (!ft_strncmp(cmd[0], "exit\0", 5))
		(ft_lstclear(data->env, (*free)), free_dp(cmd), close(data->std_
				[STDIN_FILENO]), close(data->std_[STDOUT_FILENO]), exit(0));
	else if (!ft_strncmp(cmd[0], "cd\0", 3))
		status = exec_cd(cmd);
	else if (!ft_strncmp(cmd[0], "export\0", 7))
		data->env = exec_export(data->env, cmd);
	else if (!ft_strncmp(cmd[0], "unset\0", 6))
		data->env = exec_unset(data->env, cmd);
	else if (!ft_strncmp(cmd[0], "echo\0", 5))
		exec_echo(cmd);
	else if (!ft_strncmp(cmd[0], "env\0", 4))
		exec_env(data->env);
	else
		status = run_execve(data, f_find_path(cmd[0], data->env), cmd);
	return (free_dp(cmd), exit_status(status));
}

void	exec_multiple_cmds(t_pipe *data)
{
	int		i;

	i = -1;
	while (++i < data->n_cmd)
	{
		if (!redir_files(data, data->all_cmd[i]))
			break ;
		if (i != data->n_cmd - 1)
			f_perror(pipe(data->pipe), "pipe");
		if (!f_perror(fork(), "fork"))
			(redirect_child(data, i), exec_cmd(data, reset_spaces(ft_split
						(reset_pipes(data->all_cmd[i]), ' '))), free_dp
				(data->all_cmd), free(data->line), close(data->std_[0]),
				close(data->std_[1]), close(data->pipe[0]), close(data->pipe[1]),
				exit(WEXITSTATUS(data->status)));
		else
		{
			if (i != 0)
				close(data->old_fd);
			if (i != data->n_cmd - 1)
				(close(data->pipe[1]), data->old_fd = data->pipe[0]);
		}
		close_fds(data);
	}
	(wait_cmds(data), data->old_fd = 0);
}

void	exec_single_cmd(t_pipe *data)
{
	if (!redir_files(data, data->all_cmd[0]))
		return ;
	if (data->infile)
		(dup2(data->infile, STDIN_FILENO), close(data->infile));
	if (data->outfile)
		(dup2(data->outfile, STDOUT_FILENO), close(data->outfile));
	data->status = exec_cmd(data, reset_spaces(ft_split(
					reset_pipes(data->all_cmd[0]), ' ')));
	close_fds(data);
}


int	run_execve(t_pipe *data, char *abs_path, char **cmd)
{
	char	**array_env;
	int		status;

	status = 0;
	if (data->n_cmd == 1 && fork())
		return (process_waiting(data), free(abs_path), WEXITSTATUS(data->status));
	array_env = lst_to_arr(data->env);
	if (!abs_path || execve(abs_path, cmd, array_env) == -1)
		(ft_printf("minishell: %s: command not found\n", cmd[0]), status = 127);
	free(abs_path);
	free_dp(array_env);
	if (data->n_cmd == 1)
		(close(data->std_[0]), close(data->std_[1]), exit(status));
	return (status);
}

