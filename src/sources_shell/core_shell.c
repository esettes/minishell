/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:11 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/05 01:53:20 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_s;

static void	free_all(t_cmd *cmd, t_pipe *p, char *old_cwd)
{
	if (old_cwd)
		free(old_cwd);
	free_cmd_tony(cmd);
	free_pipe_struct(p);
	// free_memory((const char **)p->env_mini,
	// 	get_array_size(p->env_mini));
	// free(p);
	// free(buff->buffer);
	// free(buff->oldbuffer);
}

static void	reset_minishell(t_cmd **cmd, t_pipe *p)
{
	if (p->buff->buffer && *p->buff->buffer && f_strict_strncmp(p->buff->buffer,
			p->buff->oldbuffer, 1024) != 0)
		add_history(p->buff->buffer);
	// reset pipe struct
	//free(p->buff->oldbuffer);
	//p->buff->oldbuffer = ft_strdup(p->buff->buffer);
	//free(p->buff->buffer);
	reset_pipe_struct(p);
	free_cmd_tony(*cmd);
	cmd = NULL;
	//free(p->childs);
	//p->childs = NULL;
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

static int	init_shell(t_pipe **p, t_buff *b, char **envp)
{
	*p = init_pipe_struct(envp);
	if (!p)
		return (EXIT_FAILURE);
	b->oldbuffer = ft_strdup("");
	signal(SIGQUIT, f_signal);
	return (EXIT_SUCCESS);
}

int	core_shell(char **envp)
{
	t_buff		b;
	t_cmd		*cmd;
	t_pipe		*p;
	char		*old_cwd;

	if (init_shell(&p, &b, envp))
		return (EXIT_FAILURE);
	old_cwd = getcwd(NULL, 0);
	while (1)
	{
		manage_signactions(MODE_STANDARD);
		signal(SIGINT, &f_signal);
		p->buff->buffer = readline("\x1b[32mminishell$\x1b[0m ");
		//b.buffer = readline("\x1b[32mminishell$\x1b[0m ");
		if (!p->buff->buffer)
		{
			//printf("no line!\n");
			free_all(cmd, p, old_cwd);
			exit(0);
		}
		if (!*p->buff->buffer || is_empty_line(p->buff->buffer))
		{
			//printf("is blank line!\n");
			free(p->buff->buffer);
			continue ;
		}
		// if (!b.buffer)
		// 	break ;
		printf("before parser \n");
		cmd = parser(b.buffer, p->env_mini);
		printf("after parser cmd: %s\n", cmd->scmd[0]);
		if (cmd == NULL)
		{
			//printf("for check if, when quotes fail, program will go through\
			//	here or not\n");
			//free(p->buff->buffer);
			continue ;
		}
		//get_cwd(old_cwd);
		run_executer(p, cmd, old_cwd);
		reset_minishell(&cmd, p);
		//printf("\x1b[33mcore shell loop!\x1b[0m\n");
	}
	free_all(cmd, p, old_cwd);
	return (EXIT_SUCCESS);
}
