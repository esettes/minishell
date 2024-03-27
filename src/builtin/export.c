/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:01:32 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/14 21:07:12 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_export(t_pipe *data, t_cmd *cmd, int pos)
{
	int	i;
	char	**envp;
	size_t	len;
	size_t	j;

	i = 0;
	j = 0;
	len = get_array_size(data->envp_minish);
	envp = malloc(sizeof(char *) * (len + 1));
	if (cmd->scmd[pos]->args[i] == NULL)
	{
		// create a new array of char * and print envp_minish in alphabetical order
		while (j < len)
		{
			envp[i] = ft_strdup(data->envp_minish[j]);
			if (data->envp_minish[j][0] == envp[i][0])
			{
				// if first letter is the same, compare second letter
				
			}
			if (data->envp_minish[j][0] > envp[i][0])
			{
				
			}
			j++;
		}
		
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
