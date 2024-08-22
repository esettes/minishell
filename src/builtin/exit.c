/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:02 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/23 00:17:09 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(t_cmd *cmd, t_pipe *d)
{
	printf("exit\n");
	free_cmd_tony(cmd);
	free_memory((const char **)d->env_mini, get_array_size(d->env_mini));
	close(d->std_[0]);
	close(d->std_[1]);
	exit (EXIT_SUCCESS);
}
