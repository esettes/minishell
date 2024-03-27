/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:10:04 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/13 23:47:51 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_unset_error(char *var);

int	exec_unset(t_cmd *cmd, t_pipe *data, int pos)
{
	t_unset	uset;

	if (!cmd->scmd[pos]->args[1])
		return (EXIT_SUCCESS);
	uset.k = 1;
	while (cmd->scmd[pos]->args[uset.k])
	{
		uset.i = 0;
		uset.j = 0;
		uset.arr_size = get_array_size(data->envp_minish);
		if (is_correct_env_variable(cmd->scmd[pos]->args[uset.k], "unset")
			&& env_var_already_exist(data->envp_minish, cmd->scmd[pos]->args[uset.k]))
		{
			uset.tmp = malloc(sizeof(char *) * uset.arr_size);
			if (!uset.tmp)
				return (EXIT_FAILURE);
			while (data->envp_minish[uset.i])
			{
				if (f_strncmp(data->envp_minish[uset.i], cmd->scmd[pos]->args[uset.k],
						f_strlen(cmd->scmd[pos]->args[uset.k])) != 0)
					{
						uset.tmp[uset.j] = f_strdup(data->envp_minish[uset.i]);
						uset.j++;
					}
				uset.i++;
			}
			uset.tmp[uset.j] = NULL;
			free_memory((const char **)data->envp_minish, uset.arr_size);
			data->envp_minish = uset.tmp;
		}
		uset.k++;
	}
	return (EXIT_SUCCESS);
}

void	print_unset_error(char *var)
{
	ft_putstrc_fd(RED_, "minishell: unset: `", 2);
	ft_putstrc_fd(RED_, var, 2);
	ft_putstrc_fd(RED_, "': not a valid identifier\n", 2);
}
