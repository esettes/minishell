/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/08 20:49:52 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args(int argc, char **envp)
{
	if (1 != argc)
		return (EXIT_FAILURE);
	if (NULL == envp)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (check_args(argc, envp))
		exit (EXIT_FAILURE);
	g_signal = 0;
	if (core_shell(envp))
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}
