/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:01:32 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/28 01:07:06 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_export(t_pipe *data, t_cmd *cmd, int pos)
{
	size_t	i;
	char	**new_env;
	size_t	len;
	size_t	j;

	i = 1;
	j = 1;
	len = get_array_size(data->envp_minish);
	new_env = malloc(sizeof(char *) * (len + 1));
	new_env[i] = NULL;
	// while (i < len)
	// {
	// 	new_env[i] = ft_strdup(data->envp_minish[i]);
	// 	i++;
	// }
	// new_env[i] = NULL;
	// i = 0;
	if (cmd->scmd[pos]->args[1] == NULL)
	{
		// create a new array of char * and print envp_minish in alphabetical order
		while (i < len)
		{
			j = i + 1;
			while (j < len)
			{
				if (ft_strncmp(new_env[i], data->envp_minish[j], 15) < 0)
				{
					
				}
				j++;
			}
			i++;
		}
		i = 0;
		while (i < len)
		{
			printf("declare -x %s\n", new_env[i]);
			i++;
		}
		free_memory((const char **)new_env, len);
	}
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
