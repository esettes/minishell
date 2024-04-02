/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:10:04 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/03 00:26:15 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void		print_unset_error(char *var);
static void	unset_variables(t_pipe *data, t_cmd *cmd, t_unset *uset, int pos);

int	exec_unset(t_cmd *cmd, t_pipe *data, int pos)
{
	t_unset	uset;

	if (!cmd->scmd[pos]->args[1])
		return (EXIT_SUCCESS);
	uset.k = 1;
	while (cmd->scmd[pos]->args[uset.k])
	{
		uset.j = 0;
		uset.arr_size = get_array_size(data->envp_minish);
		if (is_correct_env_variable(cmd->scmd[pos]->args[uset.k], "unset")
			&& env_var_already_exist(data->envp_minish,
								cmd->scmd[pos]->args[uset.k]))
		{
			uset.tmp = malloc(sizeof(char *) * uset.arr_size);
			if (!uset.tmp)
				return (EXIT_FAILURE);
			unset_variables(data, cmd, &uset, pos);
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

static void	unset_variables(t_pipe *data, t_cmd *cmd, t_unset *uset, int pos)
{
	char	*var;
	char	*value;
	uset->i = 0;

	while (data->envp_minish[uset->i])
	{
		//printf("data->envp_minish[uset->i]: %s\n", data->envp_minish[uset->i]);
		//printf("cmd->scmd[pos]->args[uset->k]: %s\n", cmd->scmd[pos]->args[uset->k]);
		var = get_env_variable(data->envp_minish[uset->i]);
		value = get_env_var_value(data->envp_minish, var);
		if (f_strncmp(data->envp_minish[uset->i], cmd->scmd[pos]->args[uset->k],
				f_strlen(cmd->scmd[pos]->args[uset->k])) != 0)
			{
				uset->tmp[uset->j] = f_strdup(data->envp_minish[uset->i]);
				uset->j++;
			}
		uset->i++;
	}
}
