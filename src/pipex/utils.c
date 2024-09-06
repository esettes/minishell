/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:08:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/09/06 23:03:50 by settes           ###   ########.fr       */
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

int	exit_status(int val)
{
	return (val << 8);
}

int	f_error(t_pipe *data)
{
	exit_s = errno;
	if (exit_s == 0)
		return (EXIT_SUCCESS);
	//perror("TEST");
	ft_putstrc_fd(RED_, "minishell: ", 2);
	ft_putstrc_fd(RED_, strerror(exit_s), 2);
	ft_putstrc_fd(RESET_, "\n", 2);
	return (exit_s);
}

int	f_perror(int status, char *s)
{
	if (status == -1)
		perror(s);
	return (status);
}

// int	duplicate_fd(int oldfd, int newfd)
// {
// 	if (dup2(oldfd, newfd) < 0)
// 		return (f_error());
// 	return (EXIT_SUCCESS);
// }

char	*get_path(char *cmd, char *path_envp)
{
	char	**paths;
	char	*path;
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

int	cmd_have_abs_path(char *cmd)
{
	register int	i;

	i = 0;
	while (cmd[i])
		if (cmd[i++] == '/')
			return (TRUE);
	return (FALSE);
}
