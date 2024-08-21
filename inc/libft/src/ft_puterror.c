/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:18:44 by uliherre          #+#    #+#             */
/*   Updated: 2024/08/21 16:30:30 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
extern volatile int	exit_s;

void	ft_puterror(const char *error)
{
	if (NULL != error)
	{
		exit_s = 127;
		write(STDERR_FILENO, "Error: ", 7 * sizeof(char));
		write(STDERR_FILENO, error, ft_strlen(error) * sizeof(char));
		write(STDERR_FILENO, "\n", sizeof(char));
	}
	exit(-42);
}

void	ft_puterror_noexit(const char *error)
{
	if (NULL != error)
	{
		exit_s = 127;
		write(STDERR_FILENO, "Error: ", 7 * sizeof(char));
		write(STDERR_FILENO, error, ft_strlen(error) * sizeof(char));
		write(STDERR_FILENO, "\n", sizeof(char));
	}
}
