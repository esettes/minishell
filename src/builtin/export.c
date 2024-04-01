/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:01:32 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/01 23:34:43 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export_no_args(char **envp_minish);
void	init_env(char **env, size_t len, char **envp_minish);

int	exec_export(t_pipe *data, t_cmd *cmd, int pos)
{
	size_t	i;

	i = 0;
	if (cmd->scmd[pos]->args[1] == NULL)
		exec_export_no_args(data->envp_minish);
	else
	{
		i = 1;
		while (cmd->scmd[pos]->args[i])
		{
			if (!is_correct_env_variable(cmd->scmd[pos]->args[i], "export"))
			{
				i++;
				continue ;
			}
			if (env_var_already_exist(data->envp_minish, cmd->scmd[pos]->args[i]))
				change_var_value(data->envp_minish, cmd->scmd[pos]->args[i]);
			else
			{
				data->envp_minish = create_new_var(data->envp_minish,
					cmd->scmd[pos]->args[i]);
				if (!data->envp_minish)
					return (EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

void	swap_str(char **env, size_t i, size_t j)
{
	char *tmp;

	tmp = env[i];
	env[i] = env[j];
	env[j] = tmp;
}

void	exec_export_no_args(char **envp_minish)
{
	size_t	i;
	char	**env;
	size_t	len;
	size_t	j;

	len = get_array_size(envp_minish);
	env = malloc(sizeof(char *) * (len + 1));
	env[len] = NULL;
	init_env(env, len, envp_minish);
	i = -1;
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (f_strncmp(env[j], env[i],
				f_strlen(env[i]) + f_strlen(env[j])) < 0)
				swap_str(env, i, j);
		}
	}
	i = -1;
	while (++i < len)
		printf("declare -x %s\n", env[i]);
	free_memory((const char **)env, len);
}

void	init_env(char **env, size_t len, char **envp_minish)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		env[i] = f_strdup(envp_minish[i]);
		i++;
	}
}
