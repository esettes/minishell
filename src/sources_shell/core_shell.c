/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:11 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/08 21:16:08 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

char	*get_prompt(t_pipe *data);

static void	free_all(t_cmd *cmd, t_pipe *p_data, t_buff *buff)
{

	free_cmd_tony(cmd);
	free(p_data->envp);
	free_memory((const char **)p_data->envp_minish,
		get_array_size(p_data->envp_minish));
	free(p_data);
	free(buff->buffer);
	free(buff->oldbuffer);
}

static void	reset_minishell(t_buff *b, char *prompt, t_cmd **cmd)
{
	if (b->buffer && *b->buffer && f_strict_strncmp(b->buffer,
			b->oldbuffer, sizeof(b->oldbuffer)) != 0)
		add_history(b->buffer);
	free (prompt);
	free(b->oldbuffer);
	b->oldbuffer = ft_strdup(b->buffer);
	free(b->buffer);
	free_cmd_tony(*cmd);
	cmd = NULL;
}
//problem with ctrl-d
int	core_shell(char **envp)
{
	t_buff	b;
	t_cmd	*cmd;
	t_pipe	*p_data;
	char	*prompt;

	p_data = init_pipe_struct(envp);
	if (!p_data)
		return (EXIT_FAILURE); 
	b.oldbuffer = ft_strdup("");
	while (1)
	{
		if (manage_signactions(MODE_STANDARD))
			return (EXIT_FAILURE);
		prompt = get_prompt(p_data);
		b.buffer = readline(prompt);
		if (!b.buffer)
			break ;
		cmd = parser(b.buffer, p_data->envp_minish);
		if (cmd == NULL)
			continue ;
		f_pipex(p_data, cmd);
		reset_minishell(&b, prompt, &cmd);
	}
	free_all(cmd, p_data, &b);
	return (EXIT_SUCCESS);
}

static void	free_prompt(t_prompt *prompt)
{
	free(prompt->curr_dir);
	free(prompt->usr);
	free(prompt->join_usr_color);
	free(prompt->join_usr_curr_dir);
	free(prompt->home_substr);
}

char	*get_prompt(t_pipe *data)
{
	t_prompt	prompt;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	prompt.home_substr = ft_substr(cwd, ft_strlen(get_env_var_value
				(data->envp_minish, "HOME")), ft_strlen(cwd));
	if (!prompt.home_substr)
		prompt.home_substr = ft_strdup(cwd);
	prompt.curr_dir = ft_strjoin(prompt.home_substr, " > ");
	if (ft_strlen(prompt.curr_dir) <= 3)
	{
		free (prompt.curr_dir);
		prompt.curr_dir = ft_strjoin(cwd, " > ");
	}
	free(cwd);
	prompt.usr = ft_strjoin(get_env_var_value(data->envp_minish, "USER"),
			" in ");
	if (!prompt.usr)
		prompt.usr = ft_strdup("minishell in ");
	prompt.join_usr_color = ft_strjoin(GREEN_, prompt.usr);
	prompt.join_usr_curr_dir = ft_strjoin(prompt.join_usr_color,
			prompt.curr_dir);
	prompt.prompt = ft_strjoin(prompt.join_usr_curr_dir, RESET_);
	free_prompt(&prompt);
	return (prompt.prompt);
}

