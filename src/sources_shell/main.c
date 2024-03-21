/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:39 by uliherre          #+#    #+#             */
/*   Updated: 2024/01/10 17:03:38 by iostancu         ###   ########.fr       */
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
	if (core_shell(envp))
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}
