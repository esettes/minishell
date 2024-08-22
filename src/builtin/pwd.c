/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:51 by iostancu          #+#    #+#             */
/*   Updated: 2024/08/23 00:17:31 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char *old_cwd)
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
