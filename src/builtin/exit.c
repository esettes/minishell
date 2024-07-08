/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:02 by iostancu          #+#    #+#             */
/*   Updated: 2024/07/08 16:45:33 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_handler(t_cmd *cmd, t_pipe *data)
{
	printf("exit\n");
	free_cmd_tony(cmd);
	close(data->std_[0]);
	close(data->std_[1]);
	exit (EXIT_SUCCESS);
}
