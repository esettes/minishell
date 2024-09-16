/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:11 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/16 16:16:48 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_waiting(t_pipe *data)
{
	(signal(SIGINT, SIG_IGN), f_perror(wait(&data->status), "wait"));
	if (WTERMSIG(data->status) == SIGINT)
		(ft_putchar_fd('\n', STDOUT_FILENO), data->status = exit_status(130));
	else if (WTERMSIG(data->status) == SIGQUIT)
		(ft_putchar_fd('\n', STDOUT_FILENO), data->status = exit_status(131));
}

void	manage_signal(int sig)
{
	if (sig != SIGINT)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	run_executer(t_pipe *data)
{
	if (data->n_cmd <= 0)
		print_err_msg(PIPE);
	f_perror(data->std_[0] = dup(STDIN_FILENO), "dup");
	f_perror(data->std_[1] = dup(STDOUT_FILENO), "dup");
	if (data->n_cmd == 1)
		exec_single_cmd(data);
	else
		exec_multiple_cmds(data);
	(dup2(data->std_[STDIN_FILENO], STDIN_FILENO),
		close(data->std_[STDIN_FILENO]));
	(dup2(data->std_[STDOUT_FILENO], STDOUT_FILENO),
		close(data->std_[STDOUT_FILENO]));
	(free_dp(data->all_cmd), free(data->line));
}

int	main(void)
{
	t_pipe	data;

	data = init_struct();
	while (1)
	{
		signal(SIGINT, &manage_signal);
		data.line = readline("\x1b[32mminishell$\x1b[0m ");
		if (!data.line)
			(ft_lstclear(data.env, (*free)), exit(0));
		if (!*data.line || !is_blank_line(data.line))
		{
			free(data.line);
			continue ;
		}
		add_history(data.line);
		data.line = quotes_checker(data.line);
		if (!data.line)
			continue ;
		data.all_cmd = expand_metachar(&data, ft_split(data.line, '|'));
		data.n_cmd = cmd_counter(data.all_cmd);
		run_executer(&data);
	}
	return (0);
}
