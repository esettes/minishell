/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:01:32 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/28 00:35:13 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export_no_args(char **envp_minish);
void	print_export_no_args(char **envp_minish, char **env, size_t len);
int		manage_variable(t_pipe *data, char *var);

int	exec_export(t_pipe *data, t_cmd *cmd, int pos)
{
	size_t	i;
	int		status;

	status = 0;
	if (cmd->scmd[pos]->args[1] == NULL)
		exec_export_no_args(data->env_mini);
	else
	{
		i = 1;
		while (cmd->scmd[pos]->args[i])
		{
			if (!is_correct_env_variable(cmd->scmd[pos]->args[i], "export"))
			{
				// print_err_msg("export", cmd->scmd[pos]->args[i],
				// 	"not a valid identifier");
				i++;
				status = 1;
				continue ;
			}
			if (manage_variable(data, cmd->scmd[pos]->args[i]))
				return (1);
			i++;
		}
	}
	return (status);
}

int	manage_variable(t_pipe *data, char *var)
{
	if (env_var_already_exist(data->env_mini, var))
		change_var_value(data->env_mini, var);
	else
	{
		data->env_mini = create_new_var(data, var);
		if (!data->env_mini)
		{
			printf("minishell: No memory\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	swap_str(char **env, size_t i, size_t j)
{
	char	*tmp;

	tmp = env[i];
	env[i] = env[j];
	env[j] = tmp;
}

void	exec_export_no_args(char **envp_minish)
{
	size_t	i;
	size_t	j;
	char	**env;
	size_t	len;

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
	print_export_no_args(envp_minish, env, len);
	free_memory((const char **)env, len);
}

void	print_export_no_args(char **envp_minish, char **env, size_t len)
{
	char	*var;
	char	*value;
	size_t	i;

	i = -1;
	while (++i < len)
	{
		var = get_env_variable(env[i]);
		printf("declare -x %s", var);
		value = get_env_var_value(envp_minish, var);
		if (value != NULL)
			printf("=\"%s\"\n", value);
		else
			printf("\n");
		free(var);
	}
}
