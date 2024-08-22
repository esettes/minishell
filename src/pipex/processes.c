/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/21 21:40:35 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int exec_process(t_pipe *data, char **cmd)
{
	char *path;
	int	status;

	status = 0;
	if (cmd_have_abs_path(cmd[0]))
	{
		path = f_strdup(cmd[0]);
		//if (execve(path, cmd, data->envp_minish) < 0)
		//	return (f_error(data));
		//return (EXIT_SUCCESS);
	}
	else
	{
		path = get_path(cmd[0], get_env_var_value(data->envp_minish, "PATH"));
	}
	printf("before fork!!\n");
	if (data->n_cmds == 1)
	{
		data->pid = fork();
		if (data->pid != 0)
		return (process_waiting(data), free(path), WEXITSTATUS(exit_s));
	}
	if (cmd_have_relative_path(cmd[0]) || !path || execve(path, cmd, data->envp_minish) == -1)
		(printf("minishell: %s: command not found\n", cmd[0]), status = 127);
	free(path);
	free(data->envp_minish);
	if (data->n_cmds == 1)
	{
		close(data->std_[R]);
		close(data->std_[W]);
		printf("exiting from exec_process!!!\n");
		exit(status);
	}
	return (status);
}

void	process_waiting(t_pipe *d)
{
	printf("in process waiting!!!\n");
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
	{
		if (exec_cd(*p_data, cmd, pos))
			return (EXIT_FAILURE);
	}
	else if (f_strncmp(*cmd->scmd[pos]->args, "pwd", sizeof("pwd")) == 0)
		pwd_handler(old_cwd);
	else if (f_strncmp(*cmd->scmd[pos]->args, "env", sizeof("env")) == 0)
	{
		if (exec_env(*p_data))
			return (EXIT_FAILURE);
	}
	else if (f_strncmp(*cmd->scmd[pos]->args, "export", sizeof("export")) == 0)
	{
		if (exec_export(*p_data, cmd, pos))
			return (EXIT_FAILURE);
	}
	else if (f_strncmp(*cmd->scmd[pos]->args, "unset", sizeof("unset")) == 0)
	{
		if (exec_unset(cmd, *p_data, pos))
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(*cmd->scmd[pos]->args, "echo", sizeof("echo")) == 0)
	{
		if (echo_handler(*cmd->scmd[pos]))
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(*cmd->scmd[pos]->args, "exit", sizeof("exit")) == 0)
	{
		if (exit_handler(cmd, *p_data))
			return (EXIT_FAILURE);
	}
	else
		status = exec_process(*p_data, cmd->scmd[pos]->args);
	printf("status single command: %i \n", status);
	printf("exit_status single command: %i \n", exit_status(status));
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

int	run_single_cmd(t_pipe *data, t_cmd *cmd, char *old_cwd)
{
	int		status;
	pid_t	cpid;

	status = 0;
	cpid = 0;
	//open_file(cmd, data, 0);
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
	//exit(status);
	return (EXIT_SUCCESS);
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
			//exit(WEXITSTATUS(status));
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
