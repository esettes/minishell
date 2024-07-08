/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:18:44 by uliherre          #+#    #+#             */
/*   Updated: 2024/04/19 23:38:13 by antosanc         ###   ########.fr       */
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
