/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:11 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/22 22:03:05 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	free_all(t_cmd *cmd, t_pipe *p_data, t_buff *buff, t_prompt	*prompt)
{
	if (prompt->old_cwd)
		free(prompt->old_cwd);
	free(prompt);
	free_memory((const char **)p_data->envp_minish,
		get_array_size(p_data->envp_minish));
	free(p_data);
	free(buff->buffer);
	free(buff->oldbuffer);
}

static void	manage_history(t_buff *b)
{
	if (b->buffer && *b->buffer && f_strict_strncmp(b->buffer,
			b->oldbuffer, sizeof(b->oldbuffer)) != 0)
		add_history(b->buffer);
	free(b->oldbuffer);
	if (b->buffer)
		b->oldbuffer = ft_strdup(b->buffer);
	else
		b->oldbuffer = NULL;
}

static void	reset_minishell(t_buff *b, t_cmd **cmd)
{
	if (b->buffer)
		free(b->buffer);
	if (cmd)
		free_cmd_tony(*cmd);
	cmd = NULL;
}

static int	init_shell(t_pipe **p_data, t_prompt **prompt, t_buff *b,
	char **envp)
{
	*p_data = init_pipe_struct(envp);
	if (!p_data)
		return (EXIT_FAILURE);
	*prompt = init_prompt();
	if (!prompt)
		return (EXIT_FAILURE);
	b->oldbuffer = ft_strdup("");
	b->buffer = NULL;
	return (EXIT_SUCCESS);
}

int	core_shell(char **envp, t_cmd *cmd, t_pipe *p_data, t_prompt *prompt)
{
	t_buff		b;

	cmd = NULL;
	if (init_shell(&p_data, &prompt, &b, envp))
		return (EXIT_FAILURE);
	while (1)
	{
		reset_minishell(&b, &cmd);
		if (manage_signactions(MODE_STANDARD))
			return (EXIT_FAILURE);
		get_prompt(p_data, prompt);
		b.buffer = readline(prompt->prompt);
		free(prompt->prompt);
		manage_history(&b);
		if (!b.buffer)
			break ;
		cmd = parser(b.buffer, p_data->envp_minish);
		if (cmd == NULL)
			continue ;
		f_pipex(p_data, cmd, prompt->old_cwd);
	}
	free_all(cmd, p_data, &b, prompt);
	return (EXIT_SUCCESS);
}
