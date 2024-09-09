/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:11 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/09 04:04:42 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_s;

static void	free_all(t_cmd *cmd, t_pipe *p_data, t_buff *buff, char *old_cwd)
{
	if (old_cwd)
		free(old_cwd);
	free_memory((const char **)p_data->env_mini,
		get_array_size(p_data->env_mini));
	free(p_data);
	free(buff->buffer);
	free(buff->oldbuffer);
}

static void	reset_minishell(t_buff *b, t_cmd **cmd, t_pipe *p)
{
	if (b->buffer && *b->buffer && f_strict_strncmp(b->buffer,
			b->oldbuffer, sizeof(b->oldbuffer)) != 0)
		add_history(b->buffer);
	free(b->oldbuffer);
	b->oldbuffer = ft_strdup(b->buffer);
	free(b->buffer);
	free_cmd_tony(*cmd);
	cmd = NULL;
	free(p->childs);
	p->childs = NULL;
}

void f_void(int sig)
{
	(void)sig;
	return ;
}

void	f_signal(int sig)
{
	if (sig != SIGINT)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

static int	init_shell(t_pipe **p_data, t_buff *b, char **envp)
{
	*p_data = init_pipe_struct(envp);
	if (!p_data)
		return (EXIT_FAILURE);
	b->oldbuffer = ft_strdup("");
	signal(SIGQUIT, f_signal);
	return (EXIT_SUCCESS);
}
static int	check_args(int argc, char **envp)
{
	if (1 != argc)
		return (EXIT_FAILURE);
	if (NULL == envp)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_buff		b;
	t_cmd		*cmd;
	t_pipe		*p_data;
	char		*old_cwd;

	(void)argv;
	if (check_args(argc, envp))
		exit (EXIT_FAILURE);
	exit_s = 0;
	if (init_shell(&p_data, &b, envp))
		return (EXIT_FAILURE);
	old_cwd = getcwd(NULL, 0);
	while (1)
	{
		if (manage_signactions(MODE_STANDARD))
			exit (EXIT_FAILURE);
		b.buffer = readline("\x1b[32mminishell$\x1b[0m ");
		if (!b.buffer)
			exit(0);
		if (!*b.buffer || is_empty_line(b.buffer))
		{
			free(b.buffer);
			continue ;
		}
		cmd = parser(b.buffer, p_data->env_mini);
		if (cmd == NULL)
		{
			free(b.buffer);
			continue ;
		}
		//get_cwd(old_cwd);
		run_executer(p_data, cmd, old_cwd);
		reset_minishell(&b, &cmd, p_data);
	}
	free_all(cmd, p_data, &b, old_cwd);
	return (EXIT_SUCCESS);
}
