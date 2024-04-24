/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:07:30 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/19 23:33:49 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_handler(t_scmd scmd)
{
	size_t	x;
	int		flag;

	x = 0;
	flag = 1;
	while (x < (size_t)scmd.argc && scmd.args[x + 1]
		&& !ft_strncmp(scmd.args[x + 1], "-n", sizeof("-n")))
	{
		flag = 0;
		x++;
	}
	while (x < (size_t)scmd.argc && scmd.args[x + 1])
	{
		ft_putstr_fd(scmd.args[x + 1], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		x++;
	}
	if (flag)
		write (STDOUT_FILENO, "\n", sizeof(char));
	return (EXIT_SUCCESS);
}
