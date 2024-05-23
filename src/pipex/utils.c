/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/23 20:38:35 by antosanc         ###   ########.fr       */
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

static char	*check_path(char *cmd, char *path_envp)
{
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(path_envp, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = f_strjoin(paths[i], "/");
		path = f_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

char	*get_path(char *cmd, char *path_envp)
{
	char	*path;

	if (ft_strncmp(".", cmd, 1) == 0)
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			return ("1");
	}
	path = check_path(cmd, path_envp);
	if (!path)
		return ("2");
	return (path);
}
