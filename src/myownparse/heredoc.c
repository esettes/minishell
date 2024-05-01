/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:52 by antosanc          #+#    #+#             */
/*   Updated: 2024/05/01 20:01:07 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static int	heredoc_write(int fd, char *delimiter, char **envp)
{
	int		bytes_written;
	char	*buff;

	while (1)
	{
		buff = readline("> ");
		if (!buff || g_signal == 130)
			return (free(buff), EXIT_FAILURE);
		if (ft_strchr(buff, '$') != 0)
			buff = expander(buff, envp, NULL);
		if (ft_strcmp(buff, delimiter) == 0)
		{
			free(buff);
			break ;
		}
		bytes_written = write(fd, buff, ft_strlen(buff));
		if (bytes_written == -1)
		{
			free(buff);
			return (perror("Failed to write to file"), EXIT_FAILURE);
		}
		write(fd, "\n", 1);
		free(buff);
	}
	return (EXIT_SUCCESS);
}

int	heredoc_init(t_scmd *scmd, t_token_lst **token_lst, char **envp)
{
	char	*delimiter;
	int		fd;

	*token_lst = (*token_lst)->next;
	delimiter = (*token_lst)->content;
	manage_signactions(MODE_HEREDOC);
	if (access("/tmp", W_OK) != 0)
		return (perror("Access denied to /tmp directory"), EXIT_FAILURE);
	scmd->in_f = ft_strdup("/tmp/heredoc");
	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Failed to open file"), EXIT_FAILURE);
	if (heredoc_write(fd, delimiter, envp))
		return (close(fd), EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}
