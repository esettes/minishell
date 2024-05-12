/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:51 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/11 15:32:39 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_handler(char *old_cwd)
{
	char	*buffer;

	buffer = getcwd(NULL, MAXPATHLEN);
	if (!buffer)
		buffer = old_cwd;
	if (buffer)
	{
		ft_putendl_fd(buffer, STDOUT_FILENO);
		free(buffer);
		return (EXIT_SUCCESS);
	}
	free(buffer);
	return (EXIT_FAILURE);
}
