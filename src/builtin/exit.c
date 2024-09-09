/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:02 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/09 07:37:32 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_numeric_symbol(char c)
{
//	int	i;

	//i = 0;
//	while (s[i])
//	{
		if (!ft_isdigit(c) && c != '"')
			return (FALSE);
//		i++;
//	}
	return (TRUE);
}

int	args_are_numeric(t_cmd *cmd, t_pipe *d)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->scmd[0]->args[i])
	{
		j = 0;
		while (cmd->scmd[0]->args[i][j])
		{
			//dprintf(2, "c: %c\n", cmd->scmd[0]->args[i][j]);
			if (!is_numeric_symbol(cmd->scmd[0]->args[i][j]) && cmd->scmd[0]->args[i][0] != '+' 
				&& cmd->scmd[0]->args[i][j] != '-')
			{
				// if (!(cmd->scmd[0]->args[i][j] == '"'))
				// {
					print_err_msg("exit", NULL, "numeric argument required");
					exit_s = 2;
					return (FALSE);
//				}
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	exec_exit(t_cmd *cmd, t_pipe *d)
{
	int	exit_code;
	char *full_arg;
	int		i;

	exit_code = 0;
	i = 0;
	// if its more than 1 args, exit (1)
	if (NULL != cmd->scmd[0]->args[2])
	{
		printf("exit\n");
		// check if 1st args is numeric symbol and 2nd arg is numeric, if true, execute
		if (cmd->scmd[0]->args[1][0] == '+' || cmd->scmd[0]->args[2][0] == '-')
		{
			while (cmd->scmd[0]->args[2][i])
			{
				if (!ft_isdigit(cmd->scmd[0]->args[2][i]))
				{
					print_err_msg("exit", NULL, "numeric argument required");
					exit_s = 2;
					return (FALSE);
				}
				i++;
			}
			if (i == ft_strlen(cmd->scmd[0]->args[2]))
			{
				if (cmd->n_scmd > 0 && cmd->scmd[0] != NULL && cmd->scmd[0]->args != NULL)
					exit_code = ft_atoi(cmd->scmd[0]->args[1]);
				printf("exit\n");
				free_cmd_tony(cmd);
				free_memory((const char **)d->env_mini, get_array_size(d->env_mini));
				close(d->std_[0]);
				close(d->std_[1]);
				exit (exit_code);
			}
		}
		print_err_msg("exit", NULL, "too many arguments");
		exit_s = 1;
		return (1);
	}
	if (!args_are_numeric(cmd, d))
		return (2);
	//if the n.1 arg is not  numeric (numeric argument required)
	if (cmd->n_scmd > 0 && cmd->scmd[0] != NULL && cmd->scmd[0]->args != NULL)
		exit_code = ft_atoi(cmd->scmd[0]->args[1]);
	printf("exit\n");
	free_cmd_tony(cmd);
	free_memory((const char **)d->env_mini, get_array_size(d->env_mini));
	close(d->std_[0]);
	close(d->std_[1]);
	exit (exit_code);
}
