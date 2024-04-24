/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:23 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/18 20:58:47 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		process_loop(t_cmd *cmd, char *envp[], t_pipe **p_data, int pos);
int		run_last_process(t_cmd *cmd, t_pipe **p_data, char *envp[], int pos);
int		open_file(t_cmd *cmd, t_pipe *data, int pos);

int	f_pipex(t_pipe *p_data, t_cmd *cmd, char *envp[])
{
	int	n_cmds;
	int	i;

	i = -1;
	n_cmds = cmd->n_scmd;
	printf("n_cmds: %d\n", n_cmds);
	while (n_cmds-- != 1)
	{
		p_data->cmd = cmd->scmd[++i]->args;
		if (process_loop(cmd, envp, &p_data, i))
			return (EXIT_FAILURE);
	}
	p_data->last_cmd = cmd->scmd[++i]->args;
	p_data->cmd = p_data->last_cmd;
	if (run_last_process(cmd, &p_data, envp, i))
		return (EXIT_FAILURE);
	n_cmds = cmd->n_scmd;
	waitpid(p_data->pid2, &g_signal, 0);
	return (EXIT_SUCCESS);
}

int	run_parent(t_cmd *cmd, t_pipe **p_data, int pos)
{
	if (f_strncmp(*cmd->scmd[pos]->args, "cd", sizeof("cd")) == 0)
		if (exec_cd(*p_data, cmd, pos))
			return (EXIT_FAILURE);
	if (f_strncmp(*cmd->scmd[pos]->args, "pwd", sizeof("pwd")) == 0)
		pwd_handler();
	if (f_strncmp(*cmd->scmd[pos]->args, "env", sizeof("env")) == 0)
		if (exec_env(*p_data))
			return (EXIT_FAILURE);
	if (f_strncmp(*cmd->scmd[pos]->args, "export", sizeof("export")) == 0)
		if (exec_export(*p_data, cmd, pos))
			return (EXIT_FAILURE);
	if (f_strncmp(*cmd->scmd[pos]->args, "unset", sizeof("unset")) == 0)
		if (exec_unset(cmd, *p_data, pos))
			return (EXIT_FAILURE);
	if (ft_strncmp(*cmd->scmd[pos]->args, "echo", sizeof("echo")) == 0)
		if (echo_handler(*cmd->scmd[pos]))
			return (EXIT_FAILURE);
	if (ft_strncmp(*cmd->scmd[pos]->args, "exit", sizeof("exit")) == 0)
		if (exit_handler(cmd))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_parent_exec(char *str)
{
	if ((f_strncmp(str, "cd", 3) == 0)
		|| (f_strncmp(str, "export", sizeof("export")) == 0)
		|| (f_strncmp(str, "unset", sizeof("unset")) == 0)
		|| (f_strncmp(str, "env", sizeof("env")) == 0)
		|| (f_strncmp(str, "pwd", sizeof("pwd")) == 0)
		|| (ft_strncmp(str, "echo", sizeof("echo")) == 0)
		|| (ft_strncmp(str, "exit", sizeof("exit")) == 0))
		return (1);
	return (0);
}

int	process_loop(t_cmd *cmd, char *envp[], t_pipe **p_data, int pos)
{
	if (pipe((*p_data)->pip) < 0)
		return (f_error());
	if (open_file(cmd, *p_data, pos))
		return (EXIT_FAILURE);
	(*p_data)->pid = fork();
	if ((*p_data)->pid < 0)
		return (f_error());
	
	if ((*p_data)->pid == 0)
		if (run_child(*p_data, cmd, envp, pos))
			return (EXIT_FAILURE);
	close((*p_data)->pip[W]);
	close_files(&(*p_data)->infile, &(*p_data)->outfile);
	if ((*p_data)->infile > -1)
		(*p_data)->infile = (*p_data)->pip[R];
	close((*p_data)->pip[R]);
	return (EXIT_SUCCESS);
}

int	run_last_process(t_cmd *cmd, t_pipe **p_data, char *envp[], int pos)
{
	if (pipe((*p_data)->pip) < 0)
		return (f_error());
	if (open_file(cmd, *p_data, pos))
		return (EXIT_FAILURE);
	if (ft_strncmp("cd", (*p_data)->last_cmd[0], sizeof("cd")) != 0
		&& ft_strncmp("exit", (*p_data)->last_cmd[0], sizeof("exit")) != 0
		//&& ft_strncmp("echo", (*p_data)->last_cmd[0], sizeof("echo")) != 0
		&& ft_strncmp("export", (*p_data)->last_cmd[0], sizeof("export")) != 0
		&& ft_strncmp("unset", (*p_data)->last_cmd[0], sizeof("unset")) != 0
		&& ft_strncmp("env", (*p_data)->last_cmd[0], sizeof("env")) != 0)
	{
		(*p_data)->pid2 = fork();
		if ((*p_data)->pid2 < 0)
			return (f_error());
		if ((*p_data)->pid2 == 0)
			if (run_child2(*p_data, cmd, envp, pos))
				return (EXIT_FAILURE);
	}
	else
		if (run_parent(cmd, p_data, pos))
			return (EXIT_FAILURE);
	close((*p_data)->pip[R]);
		close((*p_data)->pip[W]);
	close_files(&(*p_data)->infile, &(*p_data)->outfile);
	return (EXIT_SUCCESS);
}
