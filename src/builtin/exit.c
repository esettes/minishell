/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:02 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/27 19:10:47 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(t_cmd *cmd, t_pipe *d)
{
	int	exit_code;
	int	i;
	char *full_arg;

	exit_code = 0;
	if (cmd->n_scmd > 0 && cmd->scmd[0] != NULL && cmd->scmd[0]->args != NULL)
		exit_code = ft_atoi(cmd->scmd[0]->args[1]);
	printf("exit\n");
	free_cmd_tony(cmd);
	free_memory((const char **)d->env_mini, get_array_size(d->env_mini));
	close(d->std_[0]);
	close(d->std_[1]);
	exit (exit_code);
}
