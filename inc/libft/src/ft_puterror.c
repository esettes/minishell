/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:18:44 by uliherre          #+#    #+#             */
/*   Updated: 2024/03/13 21:31:36 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
extern volatile int	g_signal;

void	ft_puterror(const char *error)
{
	if (NULL != error)
	{
		g_signal = 127;
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
		g_signal = 127;
		write(STDERR_FILENO, "Error: ", 7 * sizeof(char));
		write(STDERR_FILENO, error, ft_strlen(error) * sizeof(char));
		write(STDERR_FILENO, "\n", sizeof(char));
	}
}
