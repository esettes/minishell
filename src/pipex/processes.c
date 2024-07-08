/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/07/08 07:10:04 by settes           ###   ########.fr       */
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
			return (f_error(data));
		return (EXIT_SUCCESS);
	}
	path = get_path(cmd[0], get_env_var_value(data->envp_minish, "PATH"));
	if ((cmd_have_current_path(cmd[0]) || !path))
	{
		free_split(cmd);
		dprintf(2, "minishell: command not found");
		g_signal = 2;
		return (EXIT_FAILURE);
	}
	if (execve(path, cmd, data->envp_minish) < 0)
		return (f_error(data));
	if (data->n_cmds == 1)
	{
		close(data->std_[R]);
		close(data->std_[W]);
	}
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_cmd *cmd, t_pipe **p_data, int pos, char *old_cwd)
{
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
		exec_process(*p_data, cmd->scmd[pos]->args);
	return (EXIT_SUCCESS);
}

void	redirect(t_pipe *data, int pos)
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

int	run_single_cmd(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd)
{
	if (cmd->scmd[pos]->in_f)
	{
		data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
		if (data->infile < 0)
			return (f_error(data));
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
		data->infile = 0;
	}
	if (cmd->scmd[pos]->out_f)
	{
		if (cmd->scmd[pos]->append)
			data->outfile = open(cmd->scmd[pos]->out_f,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			data->outfile = open(cmd->scmd[pos]->out_f,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile < 0)
			return (f_error(data));
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
		data->outfile = 0;
	}
	// if (!is_parent_exec(cmd->scmd[pos]->args[0]))
	// {
		data->pid = fork();
		if (data->pid < 0)
			return (f_error(data));
		if (data->pid == 0)
			data->status = exec_cmd(cmd, &data, pos, old_cwd);
	// }
	// else
	// 	run_parent(cmd, &data, 0, old_cwd);
	close_fds(data);
	return (data->status);
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

int	run_multiple_cmd(t_pipe *data, t_cmd *cmd, char *old_cwd)
{
	int	i;

	i = -1;
	while (++i < data->cmd_counter)
	{
		open_file(cmd, data, i);
		if (i !=data->cmd_counter - 1)
		{
			if (pipe(data->pip) < 0)
				return (f_error(data));
		}
		data->pid = fork();
		if (data->pid == 0)
		{
			redirect(data, i);
			if (exec_cmd(cmd, &data, i, old_cwd))
				return (EXIT_FAILURE);
			close(data->std_[R]);
			close(data->std_[W]);
			close(data->pip[0]);
			close(data->pip[1]);
			exit(WEXITSTATUS(0));
		}
		else
		{
			if ( i != 0)
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
