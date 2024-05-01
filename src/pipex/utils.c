/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/23 22:40:02 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

int	ff_error(char *num)
{
	if (!num)
		g_signal = 0;
	else
	{
		g_signal = ft_atoi(num);
		free(num);
	}
	if (g_signal == 0 || g_signal == 127)
		return (g_signal);
	ft_putstrc_fd(RED_, "minishell: ", 2);
	ft_putstrc_fd(RED_, strerror(g_signal), 2);
	ft_putstrc_fd(RESET_, "\n", 2);
	return (g_signal);
}

int	f_error(void)
{
	g_signal = errno;
	if (g_signal == 0)
		return (EXIT_SUCCESS);
	ft_putstrc_fd(RED_, "minishell: ", 2);
	ft_putstrc_fd(RED_, strerror(g_signal), 2);
	ft_putstrc_fd(RESET_, "\n", 2);
	return (EXIT_FAILURE);
}

int	duplicate_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		return (f_error());
	return (EXIT_SUCCESS);
}
