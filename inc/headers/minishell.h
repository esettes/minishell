/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 19:03:59 by iostancu          #+#    #+#             */
/*   Updated: 2024/05/01 18:35:12 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>	
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/param.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "../libft/inc/libft.h"
# include "pipex.h"
# include "parser.h"
# include "structs.h"
# include "builtin.h"

# include <readline/readline.h>
# include <readline/history.h>

# define MODE_HEREDOC 1
# define MODE_STANDARD 0

extern int	g_signal;

int	core_shell(char **envp);
int manage_signactions(int mode);
int	disable_signal(void);

#endif
