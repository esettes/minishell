/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/28 00:27:46 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

int exec_process(t_pipe *data, char **cmd)
{
	char *path;
	int	status;

	status = 0;
	if (cmd_have_abs_path(cmd[0]))
		path = f_strdup(cmd[0]);
	else
		path = get_path(cmd[0], get_env_var_value(data->env_mini, "PATH"));
	if (data->n_cmds == 1)
	{
		data->pid = fork();
		if (data->pid != 0)
			return (process_waiting(data), free(path), WEXITSTATUS(exit_s));
	}
	//if (cmd_have_relative_path(cmd[0]) || !path
	if (!path || execve(path, cmd, data->env_mini) == -1)
		(printf("minishell: %s: command not found\n", cmd[0]), status = 127);
	free(path);
	if (data->n_cmds == 1)
	{
		close(data->std_[R]);
		close(data->std_[W]);
		exit(status);
	}
	return (status);
}

void	process_waiting(t_pipe *d)
{
	(signal(SIGINT, SIG_IGN), f_perror(wait(&exit_s), "wait"));
	if (WTERMSIG(exit_s) == SIGINT)
		(ft_putchar_fd('\n', STDOUT_FILENO), exit_s = exit_status(130));
	else if (WTERMSIG(exit_s) == SIGQUIT)
		(ft_putchar_fd('\n', STDOUT_FILENO), exit_s = exit_status(131));
}

int exec_cmd(t_cmd *cmd, t_pipe **p_data, int pos, char *old_cwd)
{
	int	status;

	status = 0;
	if (f_strncmp(*cmd->scmd[pos]->args, "cd", sizeof("cd")) == 0)
		status = exec_cd(*p_data, cmd, pos);
	else if (f_strncmp(*cmd->scmd[pos]->args, "pwd", sizeof("pwd")) == 0)
		exec_pwd(old_cwd);
	else if (f_strncmp(*cmd->scmd[pos]->args, "env", sizeof("env")) == 0)
		exec_env(*p_data);
	else if (f_strncmp(*cmd->scmd[pos]->args, "export", sizeof("export")) == 0)
		status = exec_export(*p_data, cmd, pos);
	else if (f_strncmp(*cmd->scmd[pos]->args, "unset", sizeof("unset")) == 0)
		status = exec_unset(cmd, *p_data, pos);
	else if (ft_strncmp(*cmd->scmd[pos]->args, "echo", sizeof("echo")) == 0)
		status = exec_echo(*cmd->scmd[pos]);
	else if (ft_strncmp(*cmd->scmd[pos]->args, "exit", sizeof("exit")) == 0)
		exec_exit(cmd, *p_data);
	else
		status = exec_process(*p_data, cmd->scmd[pos]->args);
	//return (exit_status(status));
	return (status);
}

void redirect(t_pipe *data, int pos)
{
	if (data->infile)
		(dup2(data->infile, STDIN_FILENO), close(data->infile));
	else if (pos != 0)
		(dup2(data->old_fd, 0), close(data->old_fd));
	if (data->outfile)
		(dup2(data->outfile, STDOUT_FILENO), close(data->outfile));
	else if (pos != data->n_cmds - 1)
		(close(data->pip[0]), dup2(data->pip[1], 1), close(data->pip[1]));
}

void close_fds(t_pipe *data)
{
	if (data->infile)
	{
		close(data->infile);
		data->infile = 0;
	}
	if (data->outfile)
	{
		close(data->outfile);
		data->outfile = 0;
	}
}

void	run_single_cmd(t_pipe *data, t_cmd *cmd, char *old_cwd)
{
	open_file(cmd, data, 0);
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
	exit_s = exec_cmd(cmd, &data, 0, old_cwd);
	close_fds(data);
}

int run_multiple_cmd(t_pipe *data, t_cmd *cmd, char *old_cwd)
{
	int i;

	i = -1;
	while (++i < data->cmd_counter)
	{
		open_file(cmd, data, i);
		if (i != data->cmd_counter - 1)
		{
			if (pipe(data->pip) < 0)
				return (f_error(data));
		}
		data->pid = fork();
		data->childs[i] = data->pid;
		if (data->pid == 0)
		{
			redirect(data, i);
			if (exec_cmd(cmd, &data, i, old_cwd))
				return (EXIT_FAILURE);
			close(data->std_[R]);
			close(data->std_[W]);
			close(data->pip[0]);
			close(data->pip[1]);
			exit(WEXITSTATUS(exit_s));
		}
		else
		{
			if (i != 0)
				close(data->old_fd);
			if (i != data->cmd_counter - 1)
			{
				close(data->pip[1]);
				data->old_fd = data->pip[0];
			}
		}
		close_fds(data);
	}
	data->old_fd = 0;
	return (EXIT_SUCCESS);
}
