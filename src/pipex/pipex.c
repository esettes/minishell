/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:23 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/09 19:56:35 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		open_file(t_cmd *cmd, t_pipe *data, int pos);

int	run_executer(t_pipe *p_data, t_cmd *cmd, char *old_cwd)
{
	int status;
	pid_t	cpid;
	pid_t	pids[cmd->n_scmd];

	status = 0;
	cpid = 0;
	p_data->cmd_counter = cmd->n_scmd;
	p_data->childs = malloc(sizeof(pid_t) * cmd->n_scmd);
	if (p_data->cmd_counter <= 0)
		print_err_msg(NULL, NULL, "syntax error near unexpected token.");
	manage_signactions(MODE_CHILD);
	p_data->std_[0] = dup(STDIN_FILENO);
	p_data->std_[1] = dup(STDOUT_FILENO);
	
	if (cmd->n_scmd == 1)
		run_single_cmd(p_data, cmd, old_cwd);
	else
	{
		run_multiple_cmd(p_data, cmd, old_cwd);
		int i = 0;
		while (i < p_data->cmd_counter)
		{
			cpid = waitpid(p_data->childs[i], &status, 0);
			i++;
		}
		exit_s = status;
	}
	if (exit_s == 512 || exit_s == 256 || exit_s == 13) // || exit_s == 2)
		exit_s = 1;
	dup2(p_data->std_[STDIN_FILENO], STDIN_FILENO);
	close(p_data->std_[STDIN_FILENO]);
	dup2(p_data->std_[STDOUT_FILENO], STDOUT_FILENO);
	close(p_data->std_[STDOUT_FILENO]);
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
