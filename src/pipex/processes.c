/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/06/07 00:22:53 by iostancu         ###   ########.fr       */
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
	if (cmd->scmd[pos]->out_f)
	{
		if (cmd->scmd[pos]->append)
			data->outfile = open(cmd->scmd[pos]->out_f,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			data->outfile = open(cmd->scmd[pos]->out_f,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->outfile < 0)
			return (f_error());
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
		data->pip[W] = data->outfile;
		close(data->pip[W]); // (?)
	}
	else
	{
		data->outfile = -1;
		//data->pip[W] = STDOUT_FILENO;
		
	}
	if (!cmd->scmd[pos]->in_f)
	{
		dup2(data->previous_out, STDIN_FILENO);
		close(data->previous_out);
	}
	else
	{
		data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
		if (data->infile < 0)
			return (f_error());
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	dup2(data->pip[R], STDIN_FILENO);
	dup2(data->pip[W], STDOUT_FILENO);
	close(data->pip[R]);
	close(data->pip[W]);
	dprintf(2, "STDOUT_FILENO: %d\n", STDOUT_FILENO);
	data->previous_out = data->pip[W];
	dprintf(2, "data->previous_out (loop): %d\n", data->previous_out);
	if (is_parent_exec(data->cmd[0]))
		run_parent(cmd, &data, pos, old_cwd);
	else
		exec_process(data, data->cmd);
	return (EXIT_SUCCESS);
}

int	run_child2(t_pipe *data, t_cmd *cmd, int pos, char *old_cwd)
{
	if (data->n_cmds == 1)
	{
		if (cmd->scmd[pos]->in_f)
		{
			data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
			if (data->infile < 0)
				return (f_error());
			dup2(data->infile, STDIN_FILENO);
			close(data->infile);
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
				return (f_error());
			dup2(data->outfile, STDOUT_FILENO);
			close(data->outfile);
		}
	}
	else
	{
		if (cmd->scmd[pos]->out_f)
		{
			if (cmd->scmd[pos]->append)
				data->outfile = open(cmd->scmd[pos]->out_f,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				data->outfile = open(cmd->scmd[pos]->out_f,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data->outfile < 0)
				return (f_error());
			dup2(data->outfile, STDOUT_FILENO);
			close(data->outfile);
		}
		else
		{
			data->outfile = -1;
			//data->pip[W] = STDOUT_FILENO;
			
		}
		if (!cmd->scmd[pos]->in_f)
		{
			dprintf(2, "previous_out: %d\n", data->previous_out);
			dup2(data->previous_out, STDIN_FILENO);
			close(data->previous_out);
		}
		else
		{
			data->infile = open(cmd->scmd[pos]->in_f, O_RDONLY, 0644);
			if (data->infile < 0)
				return (f_error());
			dup2(data->infile, STDIN_FILENO);
			close(data->infile);
		}
	}
	dup2(data->pip[R], STDIN_FILENO);
	dup2(data->pip[W], STDOUT_FILENO);
	close(data->pip[R]);
	close(data->pip[W]);
	if (is_parent_exec(data->cmd[0]))
		run_parent(cmd, &data, pos, old_cwd);
	else
		exec_process(data, data->cmd);
	exit(g_signal);
	return (EXIT_SUCCESS);
}
