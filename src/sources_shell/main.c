/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/21 16:30:30 by settes           ###   ########.fr       */
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
	exit_s = 0;
	if (core_shell(envp))
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}
