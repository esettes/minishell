/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:30 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/28 00:17:43 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_num_scmd_args(t_scmd scmd)
{
	int	i;

	i = 0;
	while (scmd.args[i])
		i++;
	return (i);
}

int	exec_echo(t_scmd scmd)
{
	size_t	x;
	int		flag;
	int		args;

	x = ZERO;
	flag = TRUE;
	args = get_num_scmd_args(scmd);
	while (x < (size_t)scmd.argc && scmd.args[x + TRUE]
		&& !ft_strncmp(scmd.args[x + TRUE], "-n", sizeof("-n")))
	{
		flag = FALSE;
		x++;
	}
	while (x < (size_t)scmd.argc && scmd.args[x + TRUE])
	{
		ft_putstr_fd(scmd.args[x + TRUE], STDOUT_FILENO);
		if (args > 1 && x < args - 2)
			ft_putstr_fd(" ", STDOUT_FILENO);
		x++;
	}
	if (flag)
		write (STDOUT_FILENO, "\n", sizeof(char));
	return (EXIT_SUCCESS);
}
