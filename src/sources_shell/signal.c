/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:45:35 by antosanc          #+#    #+#             */
/*   Updated: 2024/05/07 20:46:23 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	c_handler_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	g_signal = 130;
}

static void	c_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 130;
}

static void	c_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\n");
}

int	manage_signactions(int mode)
{
	struct sigaction	s0;

	if (mode == MODE_HEREDOC)
		s0.sa_handler = &c_handler_heredoc;
	else if (mode == MODE_STANDARD)
		s0.sa_handler = &c_handler;
	else if (mode == MODE_CHILD)
		s0.sa_handler = &c_handler_child;
	s0.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s0, NULL))
		return (ft_puterror("error: sigaction\n"), EXIT_FAILURE);
	s0.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s0, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*int	disable_signal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		return (perror("tcgetattr"), EXIT_FAILURE);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		return (perror("tcgetattr"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}*/
