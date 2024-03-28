/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:01:32 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/28 01:05:01 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_export(t_pipe *data, t_cmd *cmd, int pos)
{
	size_t	i;
	char	**new_env;
	char	**aux;
	char 	tmp[200];
	size_t	len;
	size_t	j;
	size_t	k;

	i = 1;
	j = 1;
	k = 0;
	len = get_array_size(data->envp_minish);
	new_env = malloc(sizeof(char *) * (len + 1));
	aux = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		aux[i] = ft_strdup(data->envp_minish[i]);
		new_env[i] = ft_strdup(data->envp_minish[i]);
		i++;
	}
	aux[i] = NULL;
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
				
				// printf("envp_minish[i]: %s\n", data->envp_minish[i]);
				// printf("envp_minish[j]: %s\n", data->envp_minish[j]);
				// printf("ft_strncmp: %d\n", ft_strncmp(data->envp_minish[j], data->envp_minish[i], 20));
				//sleep(1);
				if (ft_strncmp(new_env[i], aux[j], 15) < 0)
				{
					ft_strlcpy(tmp, new_env[i], 200);
					ft_strlcpy(new_env[i], aux[j], sizeof(new_env[i]) + sizeof(aux[j]) + 1);
					ft_strlcpy(new_env[j], tmp, 200);
					// new_env[k] = ft_strdup(data->envp_minish[i]);
					// k++;
					// j = i;
				}
				j++;
			}
			i++;
		}
		new_env[k] = NULL;
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
