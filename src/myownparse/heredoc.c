/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:52 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/17 21:54:00 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static int	heredoc_write(int fd, char *delimiter)
{
	int	bytes_written;
	char	*buff;

	while (1)
	{
		buff = readline("> ");
		if (!buff)
			return (EXIT_FAILURE);
		if (ft_strncmp(buff, delimiter, ft_strlen(delimiter)) == 0)
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
		free(buff);
	}
	return (EXIT_SUCCESS);
}

int	heredoc_init(t_scmd *scmd, t_token_lst **token_lst)
{
	char	*delimiter;
	int		fd;

	*token_lst = (*token_lst)->next;	
	delimiter = (*token_lst)->content;
	scmd->in_f = ft_strdup(".tmp");
	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Failed to open file"), EXIT_FAILURE);
	if (heredoc_write(fd, delimiter))
		return (close(fd), EXIT_FAILURE);
	close(fd);
	
	return (EXIT_SUCCESS);
}