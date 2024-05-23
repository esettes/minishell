/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:38:33 by antosanc          #+#    #+#             */
/*   Updated: 2024/05/23 21:45:46 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_simple_envp(t_pipe *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	data->envp_minish = create_new_var(data,
			"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:"
			"/usr/bin:/sbin:/bin:/home/ubuntu/.local/bin");
	data->envp_minish = create_new_var(data, "PWD=");
	change_var_value(data->envp_minish, f_strjoin("PWD=", cwd));
	free(cwd);
}

int	is_directory(char *path)
{
	struct stat	stadtbuf;

	if (stat(path, &stadtbuf) != 0)
		return (0);
	return (S_ISDIR(stadtbuf.st_mode));
}