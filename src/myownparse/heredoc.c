/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:52 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/16 16:24:30 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	close(STDIN_FILENO);
}

int	reading_doc(char *keyword)
{
	char	*appended_line;
	int		pip[2];
	int		stdin_cp;

	stdin_cp = dup(STDIN_FILENO);
	signal(SIGINT, &heredoc_handler);
	f_perror(pipe(pip), "pipe");
	while (1)
	{
		appended_line = readline("> ");
		if (!appended_line)
			break ;
		if (!ft_strncmp(appended_line, keyword, ft_strlen(appended_line) + 1))
			break ;
		(ft_putstr_fd(appended_line, pip[1]), ft_putchar_fd('\n', pip[1]));
		free(appended_line);
	}
	if (appended_line)
		free(appended_line);
	(close(pip[1]), dup2(stdin_cp, STDIN_FILENO), close(stdin_cp));
	return (pip[0]);
}

void	here_doc(t_pipe *data, char *keyword)
{
	static int	i;
	int			heredoc_fd;

	if (i > 0)
		dup2(data->std_[STDIN_FILENO], STDIN_FILENO);
	heredoc_fd = reading_doc(keyword);
	if (data->old_fd)
		(close(data->old_fd), data->old_fd = heredoc_fd);
	else
		(dup2(heredoc_fd, STDIN_FILENO), close(heredoc_fd));
	i++;
}
