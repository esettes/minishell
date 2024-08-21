/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:05:06 by antosanc          #+#    #+#             */
/*   Updated: 2024/08/21 21:57:01 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*init_prompt(void)
{
	t_prompt	*prompt;

	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->old_cwd = NULL;
	return (prompt);
}

static void	free_prompt(t_prompt *prompt)
{
	free(prompt->curr_dir);
	free(prompt->usr);
	free(prompt->join_usr_color);
	free(prompt->join_usr_curr_dir);
	free(prompt->home_substr);
}

static void	create_prompt(t_pipe *data, t_prompt *prompt, char *cwd)
{
	if (get_env_var_value(data->envp_minish, "HOME"))
		prompt->home_substr = ft_substr(cwd, ft_strlen(get_env_var_value
					(data->envp_minish, "HOME")), ft_strlen(cwd));
	else
		prompt->home_substr = ft_strdup(cwd);
	prompt->curr_dir = ft_strjoin(prompt->home_substr, " > ");
	if (ft_strlen(prompt->curr_dir) <= 3)
	{
		free (prompt->curr_dir);
		prompt->curr_dir = ft_strjoin(cwd, " > ");
	}
	prompt->usr = ft_strjoin(get_env_var_value(data->envp_minish, "USER"),
			" in ");
	if (!prompt->usr)
		prompt->usr = ft_strdup("minishell in ");
	prompt->join_usr_color = ft_strjoin(GREEN_, prompt->usr);
	prompt->join_usr_curr_dir = ft_strjoin(prompt->join_usr_color,
			prompt->curr_dir);
	prompt->prompt = ft_strjoin(prompt->join_usr_curr_dir, RESET_);
}

void	get_prompt(t_pipe *data, t_prompt *prompt)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = prompt->old_cwd;
	else
	{
		if (prompt->old_cwd)
			free(prompt->old_cwd);
		prompt->old_cwd = ft_strdup(cwd);
	}
	create_prompt(data, prompt, cwd);
	if (cwd != prompt->old_cwd)
		free(cwd);
	free_prompt(prompt);
}

char	*get_cwd(char *old_cwd)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(old_cwd);
		free(old_cwd);
	else
	{
		if (old_cwd)
			free(old_cwd);
		old_cwd = ft_strdup(cwd);
	}
	if (f_strict_strncmp(cwd, old_cwd, 150) != 0)
		free(cwd);
	return (cwd);
}
